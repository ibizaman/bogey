#include "KeyboardState.h"

KeyboardState::KeyboardState()
    : moveForward(false),
      moveBackward(false),
      moveLeft(false),
      moveRight(false),
      moveUp(false),
      moveDown(false),
      rotateHorizontally(0),
      rotateVertically(0),
      sprint(false)
{
}

void KeyboardState::reset() {
    moveForward = false;
    moveBackward = false;
    moveLeft = false;
    moveRight = false;
    moveUp = false;
    moveDown = false;
    rotateHorizontally = 0;
    rotateVertically = 0;
    sprint = false;
}
