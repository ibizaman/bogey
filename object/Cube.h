#ifndef CUBE_H
#define CUBE_H

#include "transform/ShapeTransform.h"
#include "factory/ShapeFactory.h"

class Cube : public ShapeTransform
{
public:
    Cube(double, osg::ref_ptr<ShapeFactory>);
};

#endif
