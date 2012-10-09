#include "PlayerState.h"

PlayerState::PlayerState()
    : moveForward(false),
      moveBackward(false),
      moveLeft(false),
      moveRight(false)
{
}

void PlayerState::reset() {
    moveForward = false;
    moveBackward = false;
    moveLeft = false;
    moveRight = false;
}
