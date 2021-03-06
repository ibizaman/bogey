#ifndef INPUTEVENTHANDLER_H
#define INPUTEVENTHANDLER_H

#include <osgGA/GUIEventHandler>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>
#include <osg/Object>
#include <osg/NodeVisitor>
#include "player/KeyboardState.h"

class InputEventHandler : public osgGA::GUIEventHandler
{
public:
    InputEventHandler(osg::ref_ptr<KeyboardState>);

    virtual bool handle(const osgGA::GUIEventAdapter&, osgGA::GUIActionAdapter&, osg::Object*, osg::NodeVisitor*);

private:
    osg::ref_ptr<KeyboardState> _state;
};
#endif
