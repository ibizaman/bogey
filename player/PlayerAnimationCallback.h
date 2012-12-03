#ifndef PLAYERANIMATIONCALLBACK_H
#define PLAYERANIMATIONCALLBACK_H

#include <osg/NodeCallback>
#include "player/KeyboardState.h"

class PlayerAnimationCallback : public osg::NodeCallback
{
public:
    PlayerAnimationCallback(osg::ref_ptr<KeyboardState>);
    virtual void operator()(osg::Node*, osg::NodeVisitor*);

private:
    osg::ref_ptr<KeyboardState> _state;
    double _previousTime;
};

#endif
