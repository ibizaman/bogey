#ifndef CIRCLE_H
#define CIRCLE_H

#include <osg/Geode>
#include <osg/PositionAttitudeTransform>
#include <string>
#include "lib/Cube.h"

class Circle : public osg::PositionAttitudeTransform

{
public:
    
    Circle(std::string type , double diameter , osg::Vec3d GPos);
    void create();

private:
    
    const std::string _type;
    const double _diameter;
    const osg::Vec3d _GPos;
    
};

#endif