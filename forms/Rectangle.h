#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <osg/Geode>
#include <osg/PositionAttitudeTransform>
#include <string>
#include "lib/Cube.h"

class Rectangle : public osg::PositionAttitudeTransform
{
    
public:
    
    Rectangle(std::string type , double length , double width , osg::Vec3d GPos);
    void create();
    
private:
    
    const std::string _type;
    const double _length;
    const double _width;
    const osg::Vec3d _GPos;
    
};
#endif 