#include "PlayerTransform.h"

PlayerTransform::PlayerTransform()
    : osg::PositionAttitudeTransform(),
      _frontSpeed(0,-70,200),
      _frontAcceleration(30),
      _frontStopAcceleration(50),
      _frontBrakeAcceleration(80),
      _sideSpeed(0,-120,120),
      _sideAcceleration(50),
      _sideStopAcceleration(60),
      _sideBrakeAcceleration(100),
      _stopTrigger(1),
      _pitch(0),
      _maxPitch(osg::PI/2 - 1e-3)
{
}

PlayerTransform::PlayerTransform(const osg::PositionAttitudeTransform& transform, const osg::CopyOp& copyop)
    : osg::PositionAttitudeTransform(transform, copyop),
      _frontSpeed(0,-70,200),
      _frontAcceleration(30),
      _frontStopAcceleration(50),
      _frontBrakeAcceleration(80),
      _sideSpeed(0,-120,120),
      _sideAcceleration(50),
      _sideStopAcceleration(60),
      _sideBrakeAcceleration(100),
      _stopTrigger(1),
      _pitch(0),
      _maxPitch(osg::PI/2 - 1e-3)
{
}

void PlayerTransform::update(double dt)
{
    switch (_frontDirection.state()) {
        case TriState::PLUS: // Forward
            if (_frontSpeed >= 0) {
                _frontSpeed += _frontAcceleration * dt;
            } else {
                _frontSpeed += _frontBrakeAcceleration * dt;
            }
            break;
        case TriState::ZERO:
            if (_frontSpeed > _stopTrigger) {
                _frontSpeed -= _frontStopAcceleration * dt;
            } else if (_frontSpeed < -_stopTrigger) {
                _frontSpeed += _frontStopAcceleration * dt;
            } else {
                _frontSpeed = 0;
            }
            break;
        case TriState::MINUS: // Backward
            if (_frontSpeed <= 0) {
                _frontSpeed -= _frontAcceleration * dt;
            } else {
                _frontSpeed -= _frontBrakeAcceleration * dt;
            }
            break;
    }

    switch (_sideDirection.state()) {
        case TriState::MINUS: // Right
            if (_sideSpeed >= 0) {
                _sideSpeed += _sideAcceleration * dt;
            } else {
                _sideSpeed += _sideBrakeAcceleration * dt;
            }
            break;
        case TriState::ZERO:
            if (_sideSpeed > _stopTrigger) {
                _sideSpeed -= _sideStopAcceleration * dt;
            } else if (_sideSpeed < -_stopTrigger) {
                _sideSpeed += _sideStopAcceleration * dt;
            } else {
                _sideSpeed = 0;
            }
            break;
        case TriState::PLUS: // Left
            if (_sideSpeed <= 0) {
                _sideSpeed -= _sideAcceleration * dt;
            } else {
                _sideSpeed -= _sideBrakeAcceleration * dt;
            }
            break;
    }

    setPosition(getPosition() + getForward() * _frontSpeed.value() * dt);
    setPosition(getPosition() + getLeft() * _sideSpeed.value() * dt);
    _frontDirection.reset();
    _sideDirection.reset();
}

void PlayerTransform::forward()
{
    ++_frontDirection;
}

void PlayerTransform::backward()
{
    --_frontDirection;
}

void PlayerTransform::left()
{
    ++_sideDirection;
}

void PlayerTransform::right()
{
    --_sideDirection;
}

void PlayerTransform::rotateHorizontally(double da)
{
    setAttitude(getAttitude() * osg::Quat(da, getUp()));
}

void PlayerTransform::rotateVertically(double da)
{
    if (_pitch + da > _maxPitch) {
        da = _maxPitch - _pitch;
    } else if (_pitch + da < -_maxPitch) {
        da = -_maxPitch - _pitch;
    }
    _pitch += da;
    setAttitude(getAttitude() * osg::Quat(da, getLeft()));
}

inline osg::Vec3d PlayerTransform::getUp()
{
    return osg::Vec3d(0,0,1);
}

inline osg::Vec3d PlayerTransform::getLeft()
{
    return getForward() ^ getUp();
}

inline osg::Vec3d PlayerTransform::getForward()
{
    osg::Vec3d attitude = getAttitude() * osg::Vec3d(1,0,0);
    attitude.z() = 0;
    attitude.normalize();
    return attitude;
}

