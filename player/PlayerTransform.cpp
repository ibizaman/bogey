#include "PlayerTransform.h"

PlayerTransform::PlayerTransform()
    : osg::PositionAttitudeTransform(),
      _frontSpeed(-7,20),
      _sideSpeed(-12,12),
      _verticalSpeed(-12,12),
      _frontMaxWalkSpeed(20),
      _frontMaxSprintSpeed(40),
      _pitch(0),
      _maxPitch(osg::PI/2 - 1e-3)
{
    init();
}

PlayerTransform::PlayerTransform(const osg::PositionAttitudeTransform& transform, const osg::CopyOp& copyop)
    : osg::PositionAttitudeTransform(transform, copyop),
      _frontSpeed(-7,20),
      _sideSpeed(-12,12),
      _verticalSpeed(-12,12),
      _frontMaxWalkSpeed(20),
      _frontMaxSprintSpeed(40),
      _pitch(0),
      _maxPitch(osg::PI/2 - 1e-3)
{
    init();
}

void PlayerTransform::init()
{
    _frontSpeed.setAcceleration(20);
    _frontSpeed.setStopAcceleration(60);
    _frontSpeed.setBrakeAcceleration(80);
    _frontSpeed.setSensibility(1);

    _sideSpeed.setAcceleration(30);
    _sideSpeed.setStopAcceleration(50);
    _sideSpeed.setBrakeAcceleration(80);
    _sideSpeed.setSensibility(1);

    _verticalSpeed.setAcceleration(30);
    _verticalSpeed.setStopAcceleration(50);
    _verticalSpeed.setBrakeAcceleration(80);
    _verticalSpeed.setSensibility(1);
}

void PlayerTransform::update(double dt)
{
    setPosition(getPosition() + getForward() * _frontSpeed.getSpeed(dt) * dt);
    setPosition(getPosition() + getLeft() * _sideSpeed.getSpeed(dt) * dt);
    setPosition(getPosition() + getUp() * _verticalSpeed.getSpeed(dt) * dt);
}

void PlayerTransform::forward()
{
    ++_frontSpeed;
}

void PlayerTransform::backward()
{
    --_frontSpeed;
}

void PlayerTransform::left()
{
    ++_sideSpeed;
}

void PlayerTransform::right()
{
    --_sideSpeed;
}

void PlayerTransform::up()
{
    ++_verticalSpeed;
}

void PlayerTransform::down()
{
    --_verticalSpeed;
}

void PlayerTransform::sprint(bool sprint)
{
    if (sprint) {
        _frontSpeed.setMaxSpeed(_frontMaxSprintSpeed);
    } else {
        _frontSpeed.setMaxSpeed(_frontMaxWalkSpeed);
    }
}

void PlayerTransform::rotateHorizontally(double da)
{
    setAttitude(getAttitude() * osg::Quat(-da, getUp()));
}

void PlayerTransform::rotateVertically(double da)
{
    if (_pitch + da > _maxPitch) {
        da = _maxPitch - _pitch;
    } else if (_pitch + da < -_maxPitch) {
        da = -_maxPitch - _pitch;
    }
    _pitch += da;
    setAttitude(getAttitude() * osg::Quat(-da, getLeft()));
}

inline osg::Vec3d PlayerTransform::getUp()
{
    return osg::Vec3d(0,0,1);
}

inline osg::Vec3d PlayerTransform::getLeft()
{
    return getUp() ^ getForward();
}

inline osg::Vec3d PlayerTransform::getForward()
{
    osg::Vec3d attitude = getAttitude() * osg::Vec3d(1,0,0);
    attitude.z() = 0;
    attitude.normalize();
    return attitude;
}

