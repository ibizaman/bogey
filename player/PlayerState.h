#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include <osg/Referenced>

class PlayerState : public osg::Referenced
{
public:
    PlayerState();
    void reset();

public:
    bool moveForward;
    bool moveBackward;
    bool moveLeft;
    bool moveRight;
    bool moveUp;
    bool moveDown;
    float rotateHorizontally;
    float rotateVertically;
    bool sprint;
};

#endif
