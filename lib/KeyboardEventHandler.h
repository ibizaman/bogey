#ifndef KEYBOARDEVENTHANDLER_H
#define KEYBOARDEVENTHANDLER_H

#include <osgGA/GUIEventHandler>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>
#include <osg/Object>
#include <osg/NodeVisitor>
#include <osg/MatrixTransform>

class KeyboardEventHandler : public osgGA::GUIEventHandler
{
public:
    typedef osg::ref_ptr<osg::MatrixTransform> Transform;
public:
    KeyboardEventHandler(Transform);

    virtual bool handle(const osgGA::GUIEventAdapter&, osgGA::GUIActionAdapter&, osg::Object*, osg::NodeVisitor*);

private:
    Transform _transform;
};
#endif
