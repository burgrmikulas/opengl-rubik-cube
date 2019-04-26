#ifndef ROTATION_HPP
#define ROTATION_HPP

#include <cmath>

class Rotation {
  private:
    int x_ = -1;  // -1 not rotating, 0 or 2 = left or right side of the cube
    int y_ = -1;
    int z_ = -1;
    float dirX_ = 0.0f; // 0.0f not rotating, 1.0f rotating alongside this axis
    float dirY_ = 0.0f;
    float dirZ_ = 0.0f;
    float angle_ = 0.0f;  // angle in degrees (starting at -90.0f or 90.0f to choose direction)
    const float speed_ = 3.0f;
  public:
    Rotation(int x, int y, int z, float dirX, float dirY, float dirZ, float angle):
    x_(x), y_(y), z_(z), dirX_(dirX), dirY_(dirY), dirZ_(dirZ), angle_(angle) {
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
    
    bool updateAngle () {
      // TODO: Take FPS rate into consideration

      if (abs(angle_) < speed_) {
        finishRotation();
        return false; // No longer rotating (finished)
      } else if (angle_ > 0) {
        angle_ -= speed_;
      } else {
        angle_ += speed_;
      }
      return true;  // Still rotating
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

  #endif