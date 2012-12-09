#ifndef BODYTRANSFORM_H
#define BODYTRANSFORM_H

#include <osg/PositionAttitudeTransform>
#include "lib/Speed.h"
#include "lib/LimitedValue.hxx"

class BodyTransform : public osg::PositionAttitudeTransform
{
public:
    BodyTransform();
    BodyTransform(const osg::PositionAttitudeTransform&, const osg::CopyOp& = osg::CopyOp::SHALLOW_COPY);

    void update(double);
    void forward();
    void backward();
    void left();
    void right();
    void up();
    void down();
    void sprint(bool);
    void rotateHorizontally(double);
    void rotateVertically(double);

protected:
    inline osg::Vec3d getUp();
    inline osg::Vec3d getLeft();
    inline osg::Vec3d getForward();

private:
    void init();
    Speed _frontSpeed;
    Speed _sideSpeed;
    Speed _verticalSpeed;
    double _frontMaxWalkSpeed;
    double _frontMaxSprintSpeed;
    double _pitch;
    double _maxPitch;
};

#endif
