#ifndef KEYBOARDSTATE_H
#define KEYBOARDSTATE_H

#include <osg/Referenced>

class KeyboardState : public osg::Referenced
{
public:
    KeyboardState();
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
