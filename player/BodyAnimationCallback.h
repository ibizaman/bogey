#ifndef BODYANIMATIONCALLBACK_H
#define BODYANIMATIONCALLBACK_H

#include <osg/NodeCallback>
#include "player/KeyboardState.h"

class BodyAnimationCallback : public osg::NodeCallback
{
public:
    BodyAnimationCallback(osg::ref_ptr<KeyboardState>);
    virtual void operator()(osg::Node*, osg::NodeVisitor*);

private:
    osg::ref_ptr<KeyboardState> _state;
    double _previousTime;
};

#endif
