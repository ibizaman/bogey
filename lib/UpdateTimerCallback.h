#ifndef UPDATETIMERCALLBACK_H
#define UPDATETIMERCALLBACK_H

#include <osg/Uniform>
#include <osg/NodeVisitor>

class UpdateTimerCallback : public osg::Uniform::Callback
{
public:
    void operator()(osg::Uniform*, osg::NodeVisitor*);
};

#endif
