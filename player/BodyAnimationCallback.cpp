#include "BodyAnimationCallback.h"
#include "player/BodyTransform.h"

BodyAnimationCallback::BodyAnimationCallback(osg::ref_ptr<KeyboardState> state)
    : _state(state),
      _previousTime(0)
{
}

void BodyAnimationCallback::operator()(osg::Node* node, osg::NodeVisitor* visitor)
{
    BodyTransform* pat(dynamic_cast<BodyTransform*>(node));

    if (pat) {

        double t = visitor->getFrameStamp()->getSimulationTime();

        if (_state->moveForward) {
            pat->forward();
        }
        if (_state->moveBackward) {
            pat->backward();
        }

        if (_state->moveLeft) {
            pat->left();
        }
        if (_state->moveRight) {
            pat->right();
        }

        if (_state->moveUp) {
            pat->up();
        }
        if (_state->moveDown) {
            pat->down();
        }

        pat->sprint(_state->sprint);

        pat->rotateVertically(_state->rotateVertically * osg::PI/2);
        _state->rotateVertically = 0;

        pat->rotateHorizontally(_state->rotateHorizontally * osg::PI/2);
        _state->rotateHorizontally = 0;

        pat->update(t - _previousTime);
        _previousTime = t;

    }

    NodeCallback::operator()(node, visitor);
}
