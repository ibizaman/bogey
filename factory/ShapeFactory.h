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

class ShapeFactory : public osg::Referenced
{
public:
    typedef std::string Key;
    typedef osg::ref_ptr<osg::Node> Node;
    typedef osg::ref_ptr<TexturedDrawable> Drawable;
    typedef osg::ref_ptr<osg::PositionAttitudeTransform> PAT;

    ShapeFactory();
    Drawable getSquare(const osg::Vec2d&, const osg::Vec2d&, double length = 1);
    PAT getCube(const osg::Vec3d&, const osg::Quat&, double size = 1);

protected:
    osg::ref_ptr<osg::PositionAttitudeTransform> getTranslatedPAT(osg::Vec3d, double);

private:
    typedef std::list<osg::Vec3d> Directions;
    Directions _cubeDirections;
};

#endif
