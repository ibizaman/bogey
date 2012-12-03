#include "PlayerState.h"

PlayerState::PlayerState()
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

void PlayerState::reset() {
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
