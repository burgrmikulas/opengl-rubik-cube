#ifndef PART_HPP
#define PART_HPP

const float verticesTemplate[] = {
  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.2f, 0.2f, 0.2f,
  -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.2f, 0.2f, 0.2f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.2f, 0.2f, 0.2f,
  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.2f, 0.2f, 0.2f,
  -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.2f, 0.2f, 0.2f,
  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.2f, 0.2f, 0.2f,

   0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.2f, 0.2f, 0.2f,
   0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.2f, 0.2f, 0.2f,
   0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.2f, 0.2f, 0.2f,
   0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.2f, 0.2f, 0.2f,
   0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.2f, 0.2f, 0.2f,
   0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.2f, 0.2f, 0.2f,

  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.2f, 0.2f, 0.2f,
   0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.2f, 0.2f, 0.2f,
   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.2f, 0.2f, 0.2f,
   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.2f, 0.2f, 0.2f,
  -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.2f, 0.2f, 0.2f,
  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.2f, 0.2f, 0.2f,

  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.2f, 0.2f, 0.2f,
   0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.2f, 0.2f, 0.2f,
   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.2f, 0.2f, 0.2f,
   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.2f, 0.2f, 0.2f,
  -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.2f, 0.2f, 0.2f,
  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.2f, 0.2f, 0.2f,

  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.2f, 0.2f, 0.2f,
   0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.2f, 0.2f, 0.2f,
   0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.2f, 0.2f, 0.2f,
   0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.2f, 0.2f, 0.2f,
  -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.2f, 0.2f, 0.2f,
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.2f, 0.2f, 0.2f,

  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.2f, 0.2f, 0.2f,
   0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.2f, 0.2f, 0.2f,
   0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.2f, 0.2f, 0.2f,
   0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.2f, 0.2f, 0.2f,
  -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.2f, 0.2f, 0.2f,
  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.2f, 0.2f, 0.2f,
};

class Part {
private:
  static const unsigned int FLOATS_PER_VERTEX = 9;
  static const unsigned int COLOR_STARTS_AT_INDEX = 6;
  int x_, y_, z_;  // initial coordinates
  float rx_, ry_, rz_ = 0.0f; // actual rotation
  float colors[3*6] = {
    // 0.0f, 0.5f, 0.8f, // Background
    0.8f, 0.0f, 0.0f,
    0.0f, 0.8f, 0.0f,
    0.0f, 0.0f, 0.8f,
    0.8f, 0.8f, 0.8f,
    0.8f, 0.0f, 0.8f,
    0.0f, 0.8f, 0.8f,
  };
public:
  Part (int x, int y, int z, int rx, int ry, int rz):
  x_(x), y_(y), z_(z), rx_(rx), ry_(ry), rz_(rz) {
    // Do nothing
  }

  int x () { return x_; }
  int y () { return y_; }
  int z () { return z_; }
  float rx () { return rx_; }
  float ry () { return ry_; }
  float rz () { return rz_; }

  void setRotation (float deltaRx, float deltaRy, float deltaRz) {
    rx_ += deltaRx;
    ry_ += deltaRy;
    rz_ += deltaRz;
    // TODO: Maintain rotation in (-180.0f, 180.0f>
  }

  bool isOuterSide (int sideIndex) {
    if (sideIndex == 0 && x_ == 0 || sideIndex == 1 && x_ == 2 ||
        sideIndex == 2 && y_ == 0 || sideIndex == 3 && y_ == 2 ||
        sideIndex == 4 && z_ == 0 || sideIndex == 5 && z_ == 2) {
      return true;
    }
    return false;
  }

  void generatePartVertices(float vertices[36 * FLOATS_PER_VERTEX]) {
    for (int i = 0; i < 36; i++) {
      for (int j =0; j < FLOATS_PER_VERTEX; j++) {
        // By default just copy from template
        vertices[i * FLOATS_PER_VERTEX + j] = verticesTemplate[i * FLOATS_PER_VERTEX + j];

        // Apply different colot on outer sides
        if (j >= COLOR_STARTS_AT_INDEX && j <= COLOR_STARTS_AT_INDEX + 3) {
          int sideIndex = i/6;  // 0-5 (left, right, bottom, top, rear, front)
          // TEST
          float intensity = 0.4f;
          if (x_ == 2 && y_ == 0 && z_ == 0) {
            intensity = 1.0f;
          }

          if (isOuterSide(sideIndex)) {
            int colorIndex = sideIndex * 3 + (j - COLOR_STARTS_AT_INDEX);
            vertices[i * FLOATS_PER_VERTEX + j] = colors[colorIndex] * intensity;
          }
        }
      }
    }
  }
};

#endif