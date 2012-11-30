#include "Speed.h"

Speed::Speed(double min, double max)
    : _speed(0, min, max)
{
}

Speed& Speed::operator++()
{
    ++_orientation;
    return *this;
}

Speed& Speed::operator--()
{
    --_orientation;
    return *this;
}

double Speed::getSpeed(double dt)
{
    switch (_orientation.state()) {
        case TriState::PLUS:
            if (_speed > _speed.getMax()) {
                _speed -= _stopAcceleration * dt;
            } else if (_speed >= 0) {
                _speed += _acceleration * dt;
            } else {
                _speed += _brakeAcceleration * dt;
            }
            break;
        case TriState::ZERO:
            if (_speed > _sensibility) {
                _speed -= _stopAcceleration * dt;
            } else if (_speed < -_sensibility) {
                _speed += _stopAcceleration * dt;
            } else {
                _speed = 0;
            }
            break;
        case TriState::MINUS:
            if (_speed < _speed.getMin()) {
                _speed += _stopAcceleration * dt;
            } else if (_speed <= 0) {
                _speed -= _acceleration * dt;
            } else {
                _speed -= _brakeAcceleration * dt;
            }
            break;
    }

    _orientation.reset();

    return _speed.value();
}

void Speed::setAcceleration(double acceleration)
{
    _acceleration = acceleration;
}

void Speed::setStopAcceleration(double stopAcceleration)
{
    _stopAcceleration = stopAcceleration;
}

void Speed::setBrakeAcceleration(double brakeAcceleration)
{
    _brakeAcceleration = brakeAcceleration;
}

void Speed::setMaxSpeed(double maxSpeed)
{
    _maxSpeed = maxSpeed;
}

void Speed::setSensibility(double sensibility)
{
    _sensibility = sensibility;
}

