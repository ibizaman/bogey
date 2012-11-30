#ifndef SPEED_H
#define SPEED_H

#include "lib/TriState.h"
#include "lib/LimitedValue.hxx"

class Speed {
public:
    Speed(double, double);
    Speed& operator++();
    Speed& operator--();
    double getSpeed(double);
    void setAcceleration(double);
    void setStopAcceleration(double);
    void setBrakeAcceleration(double);
    void setMaxSpeed(double);
    void setSensibility(double);
private:
    TriState _orientation;
    LimitedValue<double> _speed;
    double _acceleration;
    double _stopAcceleration;
    double _brakeAcceleration;
    double _maxSpeed;
    double _sensibility;
};

#endif
