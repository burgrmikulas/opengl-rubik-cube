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

#include "cube.hpp"
#include "part.hpp"
#include "rotation.hpp"

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

// Init cube data model
Cube *cube = new Cube();
bool shuffling = false;
bool solving = false;

int main()
{
  /* initialize random seed: */
  srand (time(NULL));

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

  unsigned int VBO[PARTS_IN_CUBE];
  unsigned int VAO[PARTS_IN_CUBE];
  glGenVertexArrays(PARTS_IN_CUBE, VAO);
  glGenBuffers(PARTS_IN_CUBE, VBO);

  for (int i = 0; i < CUBE_SIZE; i++) {
    for (int j = 0; j < CUBE_SIZE; j++) {
      for (int k = 0; k < CUBE_SIZE; k++) {
        // generate vertices array
        Part *part = cube->part(i, j, k);
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
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection    = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    
    // retrieve the matrix uniform locations
    unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
    unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");
    
    // pass them to the shaders    
    ourShader.setMat4("view", view);
    ourShader.setMat4("projection", projection);
    ourShader.setVec3("viewPos", glm::vec3(0.0f, 0.0f, 3.0f));

    if (cube->isRotating()) {
      cube->proceedRotation();
    } else if (shuffling) {
      // Rotating randomly
      int axis = rand() % 3;  // 0 - 2
      int side = (rand() % 2) * 2; // 0 or 2
      float direction = rand() % 2 ? -90.0f : 90.0f; // -90.0f or 90.0f
      
      if (axis == 0) {
        cube->startRotation(side, -1, -1, direction);
      } else if (axis == 1) {
        cube->startRotation(-1, side, -1, direction);
      } else if (axis == 2) {
        cube->startRotation(-1, -1, side, direction);
      }
    } else if (solving) {
      // TEST: Top cross

      // Find location of the [1, 2, 2]
      int x, y, z;
      for (int i = 0; i < CUBE_SIZE; i++) {
        for (int j = 0; j < CUBE_SIZE; j++) {
          for (int k = 0; k < CUBE_SIZE; k++) {
            if (cube->part(i, j, k)->isOriginedAt(1, 2, 2)) {
              x = i;
              y = j;
              z = k;
            }
          }
        }
      }
      // If positioned in middle layer
      if (y == 1) {
        
      }
    }

    for (int i = 0; i < CUBE_SIZE; i++) {
      for (int j = 0; j < CUBE_SIZE; j++) {
        for (int k = 0; k < CUBE_SIZE; k++) {
          // Init empty model and part pointer
          glm::mat4 model = glm::mat4(1.0f);
          Part *part = cube->part(i, j, k);

          // Animated rotation
          if (cube->isRotating()) {
            if (i == cube->rotation()->x() || j == cube->rotation()->y() || k == cube->rotation()->z()) {
              model = glm::rotate(model, glm::radians(cube->rotation()->angle()), glm::vec3(cube->rotation()->dirX(), cube->rotation()->dirY(), cube->rotation()->dirZ()));
            }
          }

          // Translations
          float x = (i - 1) * PARTS_SPAN;
          float y = (j - 1) * PARTS_SPAN;
          float z = (k - 1) * PARTS_SPAN;
          model = glm::translate(model, glm::vec3(x, y, z));
          
          // Rotations
          model = model * part->rotation();

          // Final model          
          ourShader.setMat4("model", model);

          // Take the correct VAO (VAO of the part which is currently sitting at this XYZ position in the cube)
          // (locating it by the part original coordinates)
          glBindVertexArray(VAO[part->x() * CUBE_SIZE * CUBE_SIZE + part->y() * CUBE_SIZE + part->z()]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
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

  if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
    shuffling = false;
    solving = false;
  }
  if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
    shuffling = true;
    solving = false;
  }
  if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
    shuffling = false;
    solving = true;
  }

  if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    cube->startRotation(2, -1, -1, 90.0f);
  if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    cube->startRotation(0, -1, -1, 90.0f);
  if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    cube->startRotation(2, -1, -1, -90.0f);
  if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    cube->startRotation(0, -1, -1, -90.0f);

  if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    cube->startRotation(-1, 2, -1, 90.0f);
  if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    cube->startRotation(-1, 0, -1, 90.0f);
  if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    cube->startRotation(-1, 2, -1, -90.0f);
  if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
    cube->startRotation(-1, 0, -1, -90.0f);

  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    cube->startRotation(-1, -1, 2, 90.0f);
  if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    cube->startRotation(-1, -1, 0, 90.0f);
  if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    cube->startRotation(-1, -1, 2, -90.0f);
  if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    cube->startRotation(-1, -1, 0, -90.0f);
    
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