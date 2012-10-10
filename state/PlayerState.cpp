#include "PlayerState.h"

PlayerState::PlayerState()
    : moveForward(false),
      moveBackward(false),
      moveLeft(false),
      moveRight(false),
      rotateHorizontally(false),
      rotateVertically(false)
{
}

void PlayerState::reset() {
    moveForward = false;
    moveBackward = false;
    moveLeft = false;
    moveRight = false;
    rotateHorizontally = false;
    rotateVertically = false;
}
