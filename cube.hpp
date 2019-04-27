#ifndef CUBE_HPP
#define CUBE_HPP

#include "part.hpp"
#include "rotation.hpp"

class Cube {
private:
  static const unsigned int CUBE_SIZE = 3;
  Part *parts_[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];
  Part *tempParts_[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];  // Used as buffer during replacing parts (rotation)
  Rotation *rotation_ = nullptr;
public:
  Cube () {
    // Initiate the parts of the cube
    for (int i = 0; i < CUBE_SIZE; i++) {
      for (int j = 0; j < CUBE_SIZE; j++) {
        for (int k = 0; k < CUBE_SIZE; k++) {
          parts_[i][j][k] = new Part(i, j, k);
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

  void startRotation (int x, int y, int z, float angle) {
    if (!isRotating()) {
      int isRotatingX = x == -1 ? 0 : 1;
      int isRotatingY = y == -1 ? 0 : 1;
      int isRotatingZ = z == -1 ? 0 : 1;

      // Move parts to new position in the cube
      for (int i = 0; i < CUBE_SIZE; i++) {
        for (int j = 0; j < CUBE_SIZE; j++) {
          for (int k = 0; k < CUBE_SIZE; k++) {
            if (i == x || j == y || k == z) {
              // - Rotate
              parts_[i][j][k]->setRotation(isRotatingX * angle, isRotatingY * angle, isRotatingZ * angle);
              // - Move (translate)
              int newI = i;
              int newJ = j;
              int newK = k;
              if (x != -1) {
                // Rotating by the X axis
                newI = i;
                if (angle > 0.0f) {
                  // Clockwise
                  newJ = CUBE_SIZE - 1 - k;
                  newK = j;
                } else {
                  newJ = k;
                  newK = CUBE_SIZE - 1 - j;
                }
                
              }
              if (y != -1) {
                // Rotating by the Y axis
                newJ = j;
                if (angle < 0.0f) { // Reversed < due to the fact that X, Z axises follow in reverse order (compared to other rotations)
                  // Clockwise
                  newI = CUBE_SIZE - 1 - k;
                  newK = i;
                } else {
                  newI = k;
                  newK = CUBE_SIZE - 1 - i;
                }
              }
              if (z != -1) {
                // Rotating by the Z axis
                newK = k;
                if (angle > 0.0f) {
                  // Clockwise
                  newI = CUBE_SIZE - 1 - j;
                  newJ = i;
                } else {
                  newI = j;
                  newJ = CUBE_SIZE - 1 - i;
                }
              }
              
              tempParts_[newI][newJ][newK] = parts_[i][j][k];
            } else {
              // Must fill-in also other parts of the tempParts so that all 27 parts are present
              tempParts_[i][j][k] = parts_[i][j][k];
            }
          }
        }
      }
      // Copy tempParts back to parts (thus updating the parts position in the cube)
      for (int i = 0; i < CUBE_SIZE; i++) {
        for (int j = 0; j < CUBE_SIZE; j++) {
          for (int k = 0; k < CUBE_SIZE; k++) {
            parts_[i][j][k] = tempParts_[i][j][k];
          }
        }
      }


      // Initiate the rotation (animation)
      // Angle must be negative (as the parts have been moved before the animation starts)
      rotation_ = new Rotation(x, y, z, -angle);

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