#ifndef CUBE_HPP
#define CUBE_HPP

#include "part.hpp"
#include "rotation.hpp"

class Cube {
private:
  static const unsigned int CUBE_SIZE = 3;
  Part *parts[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];
  Rotation *rotation_ = nullptr;
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

  void rotateCube (int x, int y, int z) { // TODO
    // TODO
    rotation_ = new Rotation();

    delete rotation_;
  }
};

#endif