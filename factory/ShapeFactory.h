#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "lib/Factory.hxx"
#include "transform/ShapeTransform.h"
#include <osg/Node>
#include <osg/PositionAttitudeTransform>
#include <osg/Vec2d>
#include <osg/Vec3d>
#include <osg/Quat>
#include <list>
#include "lib/TexturedDrawable.h"

class ShapeFactory : public Factory<ShapeTransform>
{
public:
    typedef Factory<ShapeTransform>::Element Element;
    typedef Factory<ShapeTransform>::const_iterator const_iterator;

    ShapeFactory(bool = false);

    typedef osg::ref_ptr<TexturedDrawable> Drawable;
    Drawable getSquare(const osg::Vec2d&, const osg::Vec2d&, double length = 1);
};

#endif
