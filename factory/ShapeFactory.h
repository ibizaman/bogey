#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include <osg/Referenced>
#include <osg/Node>
#include <osg/PositionAttitudeTransform>
#include <osg/Vec2d>
#include <osg/Vec3d>
#include <osg/Quat>
#include <list>
#include "lib/TexturedDrawable.h"
#include "transform/ShapeTransform.h"

class ShapeFactory : public osg::Referenced
{
public:
    typedef osg::ref_ptr<ShapeTransform> Cube;

    ShapeFactory();
    Cube getCube(const osg::Vec3d&, const osg::Quat&, double size = 1);

protected:

private:
    typedef osg::ref_ptr<TexturedDrawable> Drawable;
    Drawable getSquare(const osg::Vec2d&, const osg::Vec2d&, double length = 1);
    void translate(osg::PositionAttitudeTransform*, osg::Vec3d, double);

    typedef std::list<osg::Vec3d> Directions;
    Directions _cubeDirections;
};

#endif
