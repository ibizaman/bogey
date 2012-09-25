#include "KeyboardEventHandler.h"
#include <osgGA/GUIEventAdapter>
#include <osg/Matrix>

KeyboardEventHandler::KeyboardEventHandler(Transform transform)
    : _transform(transform)
{
}

bool KeyboardEventHandler::handle(const osgGA::GUIEventAdapter& event, osgGA::GUIActionAdapter& action, osg::Object* obj, osg::NodeVisitor* visitor)
{
    (void) action;
    (void) obj;
    (void) visitor;
    osg::Matrix matrix(_transform->getMatrix());
    switch (event.getEventType()) {
        case osgGA::GUIEventAdapter::KEYDOWN:
            switch (event.getKey()) {
                case 'z': case 'Z':
                    matrix *= osg::Matrix::translate(.1,0,0);
                    break;
                case 's': case 'S':
                    matrix *= osg::Matrix::translate(-.1,0,0);
                    break;
                case 'q': case 'Q':
                    matrix *= osg::Matrix::rotate(-0.1, osg::Z_AXIS);
                    break;
                case 'd': case 'D':
                    matrix *= osg::Matrix::rotate(0.1, osg::Z_AXIS);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    _transform->setMatrix(matrix);
    return false;
}
