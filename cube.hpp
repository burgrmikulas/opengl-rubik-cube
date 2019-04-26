#ifndef CUBE_HPP
#define CUBE_HPP

#include "part.hpp"
#include "rotation.hpp"

class Cube {
private:
  static const unsigned int CUBE_SIZE = 3;
  Part *parts_[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];
  Rotation *rotation_ = nullptr;
public:
  Cube () {
    // Initiate the parts of the cube
    for (int i = 0; i < CUBE_SIZE; i++) {
      for (int j = 0; j < CUBE_SIZE; j++) {
        for (int k = 0; k < CUBE_SIZE; k++) {
          parts_[i][j][k] = new Part(i, j, k, 0.0f, 0.0f, 0.0f);
        }
      }
    }
  }
  
  Part *part (int x, int y, int z) {
    return parts_[x][y][z];
  }

  Rotation *rotation () {
    return rotation_;
  }

  bool isRotating () {
    return rotation_ != nullptr;
  }

  void startRotation (int x, int y, int z, float dirX, float dirY, float dirZ, float angle) {
    if (!isRotating()) {
      // Initiate the rotation (animation)
      rotation_ = new Rotation(x, y, z, dirX, dirY, dirZ, angle);

      // Move parts to new position in the cube
      // - Rotate
      // TODO
      // for (int i = 0; i < CUBE_SIZE; i++) {
      //   for (int j = 0; j < CUBE_SIZE; j++) {
      //     for (int k = 0; k < CUBE_SIZE; k++) {
      //       if (i == rotation_->x() || j == rotation_->y() || rotation_->z()) {
      //         parts_[i][j][k]->setRotation(-dirX * angle, dirY * angle, dirZ * angle);
      //       }
      //     }
      //   }
      // }
      // - Move (translate)
      // TODO
    }
  }

  void proceedRotation () {
    if (rotation_) {
      bool stillRotating = rotation_->updateAngle();
      if (!stillRotating) {
        finishRotation();
      }
    }
  }

  void finishRotation () {
    delete rotation_;
    rotation_ = nullptr;
  }
};

#endif