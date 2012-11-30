#include "PlayerAnimationCallback.h"
#include "transform/PlayerTransform.h"

PlayerAnimationCallback::PlayerAnimationCallback(osg::ref_ptr<PlayerState> state)
    : _state(state),
      _previousTime(0)
{
}

void PlayerAnimationCallback::operator()(osg::Node* node, osg::NodeVisitor* visitor)
{
    PlayerTransform* pat(dynamic_cast<PlayerTransform*>(node));

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
