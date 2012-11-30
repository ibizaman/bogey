#include "InputEventHandler.h"

InputEventHandler::InputEventHandler(osg::ref_ptr<PlayerState> state)
    : _state(state)
{
}

bool InputEventHandler::handle(const osgGA::GUIEventAdapter& event, osgGA::GUIActionAdapter& action, osg::Object* obj, osg::NodeVisitor* visitor)
{
    (void) action;
    (void) obj;
    (void) visitor;

    bool handled = true;
    switch (event.getEventType()) {

        case osgGA::GUIEventAdapter::MOVE:
            _state->rotateHorizontally -= event.getXnormalized();
            _state->rotateVertically += event.getYnormalized();
            action.requestWarpPointer((event.getXmin()+event.getXmax())/2, (event.getYmin()+event.getYmax())/2);
            break;

        case osgGA::GUIEventAdapter::KEYDOWN:
            switch (event.getKey()) {
                case 'z': case 'Z':
                    _state->moveForward = true;
                    break;
                case 's': case 'S':
                    _state->moveBackward = true;
                    break;
                case 'q': case 'Q':
                    _state->moveLeft = true;
                    break;
                case 'd': case 'D':
                    _state->moveRight = true;
                    break;
                case osgGA::GUIEventAdapter::KEY_Space:
                    _state->moveUp = true;
                    break;
                case osgGA::GUIEventAdapter::KEY_Control_L:
                    _state->moveDown = true;
                    break;
                case osgGA::GUIEventAdapter::KEY_Shift_L:
                    _state->sprint = true;
                    break;
                default:
                    handled = false;
                    break;
            }
            break;

        case osgGA::GUIEventAdapter::KEYUP:
            switch (event.getKey()) {
                case 'z': case 'Z':
                    _state->moveForward = false;
                    break;
                case 's': case 'S':
                    _state->moveBackward = false;
                    break;
                case 'q': case 'Q':
                    _state->moveLeft = false;
                    break;
                case 'd': case 'D':
                    _state->moveRight = false;
                    break;
                case osgGA::GUIEventAdapter::KEY_Space:
                    _state->moveUp = false;
                    break;
                case osgGA::GUIEventAdapter::KEY_Control_L:
                    _state->moveDown = false;
                    break;
                case osgGA::GUIEventAdapter::KEY_Shift_L:
                    _state->sprint = false;
                    break;
                default:
                    handled = false;
                    break;
            }
            break;
        default:
            handled = false;
            break;
    }

    return handled;
}
