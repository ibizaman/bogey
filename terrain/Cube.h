#ifndef CUBE_H
#define CUBE_H

#include "terrain/ShapeTransform.h"
#include "terrain/ShapeFactory.h"

class Cube : public ShapeTransform
{
public:
    Cube(double, osg::ref_ptr<ShapeFactory>);
};

#endif
