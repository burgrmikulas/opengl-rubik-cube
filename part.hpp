#ifndef PART_HPP
#define PART_HPP

const float verticesTemplate[] = {
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.5f, 0.8f,
   0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.5f, 0.8f,
   0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.5f, 0.8f,
   0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.5f, 0.8f,
  -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.5f, 0.8f,
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.5f, 0.8f,

  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.5f, 0.8f,
   0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.5f, 0.8f,
   0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.5f, 0.8f,
   0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.5f, 0.8f,
  -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.5f, 0.8f,
  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.5f, 0.8f,

  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,

   0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
   0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
   0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
   0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
   0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,
   0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.5f, 0.8f,

  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
   0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.5f, 0.8f,

  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
   0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.5f, 0.8f,
};

class Part {
private:
  static const unsigned int FLOATS_PER_VERTEX = 9;
  static const unsigned int COLOR_STARTS_AT_INDEX = 6;
  int x_, y_, z_;  // initial coordinates
  float rx_, ry_, rz_ = 0.0f; // actual rotation
  float colors[3*6] = {
    0.0f, 0.5f, 0.8f, // Background
    1.0f, 0.5f, 0.8f,
    0.0f, 1.0f, 0.8f,
    0.0f, 0.5f, 1.0f,
    0.0f, 0.5f, 0.0f,
    0.8f, 0.8f, 1.0f, 
  };
public:
  Part (int x, int y, int z, int rx, int ry, int rz):
  x_(x), y_(y), z_(z), rx_(rx), ry_(ry), rz_(rz) {
    // Do nothing
  }

  float x () { return x_; }
  float y () { return y_; }
  float z () { return z_; }
  float rx () { return rx_; }
  float ry () { return ry_; }
  float rz () { return rz_; }

  void setRotation (float deltaRx, float deltaRy, float deltaRz) {
    rx_ += deltaRx;
    ry_ += deltaRy;
    rz_ += deltaRz;
    // TODO: Maintain rotation in (-180.0f, 180.0f>
  }

  void generatePartVertices(float vertices[36 * FLOATS_PER_VERTEX]) {
    for (int i = 0; i < 36; i++) {
      for (int j =0; j < FLOATS_PER_VERTEX; j++) {
        if (j >= COLOR_STARTS_AT_INDEX && j <= COLOR_STARTS_AT_INDEX + 3) {
          // Use defined color
          int colorIndex = (i/6) * 3 + (j - COLOR_STARTS_AT_INDEX);
          vertices[i * FLOATS_PER_VERTEX + j] = colors[colorIndex];
        } else {
          // Just copy from template
          vertices[i * FLOATS_PER_VERTEX + j] = verticesTemplate[i * FLOATS_PER_VERTEX + j];
        }
      }
    }
  }
};

#endif