#ifndef PLAYERANIMATIONCALLBACK_H
#define PLAYERANIMATIONCALLBACK_H

#include <osg/NodeCallback>
#include "state/PlayerState.h"

class PlayerAnimationCallback : public osg::NodeCallback
{
public:
    PlayerAnimationCallback(osg::ref_ptr<PlayerState>);
    virtual void operator()(osg::Node*, osg::NodeVisitor*);

private:
    osg::ref_ptr<PlayerState> _state;
    double _previousTime;
};

#endif
