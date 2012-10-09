#ifndef PLAYERTRANSFORM_H
#define PLAYERTRANSFORM_H

#include <osg/PositionAttitudeTransform>
#include "lib/TriState.h"
#include "lib/LimitedValue.hxx"

class PlayerTransform : public osg::PositionAttitudeTransform
{
public:
    PlayerTransform();
    PlayerTransform(const osg::PositionAttitudeTransform&, const osg::CopyOp& = osg::CopyOp::SHALLOW_COPY);

    void update(double);
    void forward();
    void backward();
    void left();
    void right();

protected:
    inline osg::Vec3d getUp();
    inline osg::Vec3d getLeft();
    inline osg::Vec3d getForward();

private:
    TriState _frontDirection;
    TriState _sideDirection;
    LimitedValue<double> _frontSpeed;
    double _frontAcceleration;
    double _frontStopAcceleration;
    double _frontBrakeAcceleration;
    LimitedValue<double> _sideSpeed;
    double _sideAcceleration;
    double _sideStopAcceleration;
    double _sideBrakeAcceleration;
    double _stopTrigger;
};

#endif
