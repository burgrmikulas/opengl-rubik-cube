#ifndef ROTATION_HPP
#define ROTATION_HPP

#include <cmath>

class Rotation {
  private:
    int x_ = -1;  // -1 not rotating, 0 or 2 = left or right side of the cube
    int y_ = -1;
    int z_ = -1;
    float angle_ = 0.0f;  // angle in degrees (starting at -90.0f or 90.0f to choose direction)
    const float speed_ = 3.0f;
  public:
    Rotation(int x, int y, int z, float angle):
    x_(x), y_(y), z_(z), angle_(angle) {
      // Empty
    }
    int x () { return x_; }
    int y () { return y_; }
    int z () { return z_; }
    void x (int value) { x_ = value; }
    void y (int value) { y_ = value; }
    void z (int value) { z_ = value; }
    float angle () { return angle_; }
    void angle (float value) { angle_ = value; }

    float dirX () {
      return x_ == -1 ? 0.0f : 1.0f; // 0.0f not rotating, 1.0f rotating alongside this axis
    }

    float dirY () {
      return y_ == -1 ? 0.0f : 1.0f;
    }
    float dirZ () {
      return z_ == -1 ? 0.0f : 1.0f;
    }
    
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