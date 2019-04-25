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
  int x, y, z;  // initial coordinates
  float rx, ry, rz = 0.0f; // actual rotation
  float colors[3*6] = {
    0.0f, 0.5f, 0.8f, // Background
    1.0f, 0.5f, 0.8f,
    0.0f, 1.0f, 0.8f,
    0.0f, 0.5f, 1.0f,
    0.0f, 0.5f, 0.0f,
    0.0f, 0.0f, 0.8f, 
  };
public:
  Part (int x, int y, int z, int rx, int ry, int rz):
  x(x), y(y), z(z), rx(rx), ry(ry), rz(rz) {
    // Do nothing
  }

  float getX () {
    return x;
  }

  float getY () {
    return y;
  }

  float getZ () {
    return z;
  }

  float getRx () {
    return rx;
  }

  float getRy () {
    return ry;
  }

  float getRz () {
    return rz;
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