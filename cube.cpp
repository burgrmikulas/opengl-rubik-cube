#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "shader.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>

#include "part.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera defaults
Camera camera(glm::vec3(7.0f, 7.0f, 7.0f));
float lastX =  SCR_WIDTH / 2.0;
float lastY =  SCR_HEIGHT / 2.0;
bool firstMouse = true;

// delta time
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

const int CUBE_SIZE = 3;
const int PARTS_IN_CUBE = CUBE_SIZE * CUBE_SIZE * CUBE_SIZE;
const float PARTS_SPAN = 1.1f;
const unsigned int VERTICES_PER_PART = 36;
const unsigned int FLOATS_PER_VERTEX = 9;

class Cube {
private:
  Part *parts[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];
public:
  Cube () {
    // Initiate the parts of the cube
    for (int i = 0; i < CUBE_SIZE; i++) {
      for (int j = 0; j < CUBE_SIZE; j++) {
        for (int k = 0; k < CUBE_SIZE; k++) {
          parts[i][j][k] = new Part(i, j, k, 0.0f, 0.0f, 0.0f);
        }
      }
    }
  }
  
  Part *getPart (int x, int y, int z) {
    return parts[x][y][z];
  }
};

int main()
{
  /* initialize random seed: */
  srand (time(NULL));

  // Init cube data model
  Cube *cube = new Cube();

  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // glfw window creation
  // --------------------
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cube", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  // tell GLFW to capture our mouse
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // configure global opengl state
  // -----------------------------
  glEnable(GL_DEPTH_TEST);

  // build and compile our shader program
  // ------------------------------------
  Shader ourShader("shader.vs", "shader.fs"); // you can name your shader files however you like

  // float vertices[] = {
  //   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.5f, 0.8f,
  //    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.5f, 0.8f,
  //    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.5f, 0.8f,
  //    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.5f, 0.8f,
  //   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.5f, 0.8f,
  //   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.5f, 0.8f,

  //   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.5f, 0.8f,
  //    0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.5f, 0.8f,
  //    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.5f, 0.8f,
  //    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.5f, 0.8f,
  //   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.5f, 0.8f,
  //   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.5f, 0.8f,

  //   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,

  //    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,

  //   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.5f, 0.8f,

  //   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  //   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  // };

  unsigned int VBO[PARTS_IN_CUBE];
  unsigned int VAO[PARTS_IN_CUBE];
  glGenVertexArrays(PARTS_IN_CUBE, VAO);
  glGenBuffers(PARTS_IN_CUBE, VBO);

  for (int i = 0; i < CUBE_SIZE; i++) {
    for (int j = 0; j < CUBE_SIZE; j++) {
      for (int k = 0; k < CUBE_SIZE; k++) {
        // generate vertices array
        Part *part = cube->getPart(i, j, k);
        float vertices[VERTICES_PER_PART * FLOATS_PER_VERTEX];
        part->generatePartVertices(vertices);

        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO[i * CUBE_SIZE * CUBE_SIZE + j * CUBE_SIZE + k]);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[i * CUBE_SIZE * CUBE_SIZE + j * CUBE_SIZE + k]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal vector attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // color attribute
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
      }
    }
  }
  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  glBindVertexArray(0);

  // uncomment this call to draw in wireframe polygons.
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // TEMP: Rotating the right side
  class Rotation {
  private:
    int x_ = -1;  // -1 not rotating, 0 or 2 = left or right side of the cube
    int y_ = -1;
    int z_ = -1;
    float dirX_ = 0.0f; // 0.0f not rotating, 1.0f rotating alongside this axis
    float dirY_ = 0.0f;
    float dirZ_ = 0.0f;
    float angle_ = 0.0f;  // angle in degrees
    const float speed_ = 3.0f;
  public:
    Rotation() {
      // Empty
    }
    int x () { return x_; }
    int y () { return y_; }
    int z () { return z_; }
    void x (int value) { x_ = value; }
    void y (int value) { y_ = value; }
    void z (int value) { z_ = value; }
    float dirX () { return dirX_; }
    float dirY () { return dirY_; }
    float dirZ () { return dirZ_; }
    void dirX (float value) { dirX_ = value; }
    void dirY (float value) { dirY_ = value; }
    void dirZ (float value) { dirZ_ = value; }
    float angle () { return angle_; }
    void angle (float value) { angle_ = value; }
    
    void updateAngle () {
      if (abs(angle_) < speed_) {
        finishRotation();
      } else if (angle_ > 0) {
        angle_ -= speed_;
      } else {
        angle_ += speed_;
      }
    }

    void finishRotation () {
      x_ = y_ = z_ = -1;
      dirX_ = dirY_ = dirZ_ = 0.0f;
      angle_ = 0.0f;
    }

    bool isRotating () {
      if ((x_ + y_ + z_) == -3) {
        return false;
      }
      return true;
    }
  };
  Rotation *rotation = new Rotation();

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
  {
    // calculating delta time
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    // input
    // -----
    processInput(window);

    // render
    // ------
    glClearColor(0.4f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ourShader.use();

    // create transformations
    // float radius = 10.0f;
    // float camX = sin(glfwGetTime()) * radius;
    // float camZ = cos(glfwGetTime()) * radius;
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection    = glm::mat4(1.0f);
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
    projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    // retrieve the matrix uniform locations
    unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
    unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");
    // pass them to the shaders
    
    ourShader.setMat4("view", view);
    ourShader.setMat4("projection", projection);
    ourShader.setVec3("viewPos", glm::vec3(0.0f, 0.0f, 3.0f));

    // TEMP: Rotating the right side
    if (!rotation->isRotating()) {
      float angle = 90.0f;
      if (rand() % 2) {
        angle = -90.0f;
      }
      int side = 0;
      if (rand() % 2) {
        side = 2;
      }
      int random02 = rand() % 3;
      if (random02 == 0) {
        rotation->x(side);
        rotation->dirX(1.0f);
      } else if (random02 == 1) {
        rotation->y(side);
        rotation->dirY(1.0f);
      } else {
        rotation->z(side);
        rotation->dirZ(1.0f);
      }
      rotation->angle(angle);
    } else {
      rotation->updateAngle();
    }    

    for (int i = 0; i < CUBE_SIZE; i++) {
      for (int j = 0; j < CUBE_SIZE; j++) {
        for (int k = 0; k < CUBE_SIZE; k++) {
          // Init empty model and part pointer
          glm::mat4 model = glm::mat4(1.0f);
          Part *part = cube->getPart(i, j, k);

          // TEMP: Rotating the right side - translation to the side center
          if (i == rotation->x() || j == rotation->y() || k == rotation->z()) {
            // model = glm::translate(model, glm::vec3(i * PARTS_SPAN, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(rotation->angle()), glm::vec3(rotation->dirX(), rotation->dirY(), rotation->dirZ()));
            float x = (i - 1) * PARTS_SPAN;
            float y = (j - 1) * PARTS_SPAN;
            float z = (k - 1) * PARTS_SPAN;
            model = glm::translate(model, glm::vec3(x, y, z));
          } else {
            // Translations
            float xPos = (i - 1) * PARTS_SPAN;
            float yPos = (j - 1) * PARTS_SPAN;
            float zPos = (k - 1) * PARTS_SPAN;
            model = glm::translate(model, glm::vec3(xPos, yPos, zPos));

            // Rotations
            model = glm::rotate(model, glm::radians(part->getRx()), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(part->getRy()), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(part->getRz()), glm::vec3(0.0f, 0.0f, 1.0f));          
          }

          // Final model          
          ourShader.setMat4("model", model);

          glBindVertexArray(VAO[i * CUBE_SIZE * CUBE_SIZE + j * CUBE_SIZE + k]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
          glDrawArrays(GL_TRIANGLES, 0, 36);
          // glBindVertexArray(0); // no need to unbind it every time 
        }
      }
    }

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(PARTS_IN_CUBE, VAO);
  glDeleteBuffers(PARTS_IN_CUBE, VBO);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();

  // Data model cleanup
  delete rotation;
  delete cube;

  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and 
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
  if (firstMouse)
  {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  camera.ProcessMouseScroll(yoffset);
}