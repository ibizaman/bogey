#include "FaceTransform.h"
#include <osg/Geode>

FaceTransform::FaceTransform(Drawable drawable)
    :_drawable(drawable)
{
    osg::ref_ptr<osg::Geode> geode(new osg::Geode());
    geode->addDrawable(_drawable);
    addChild(geode);
}

void FaceTransform::setDirectionAndShift(const osg::Vec3d& direction, double shift)
{
    osg::Quat finalRot = computeQuat(direction);

    setAttitude(finalRot);
    setPosition(direction*shift);

    for (TexturedDrawable::normalsIterator normal = _drawable->normalsBegin(); normal != _drawable->normalsEnd(); ++normal)
    {
        *normal = (finalRot * *normal);
    }
}

osg::Quat FaceTransform::computeQuat(osg::Vec3d direction)
{
    direction.normalize();

    double zAngle = atan2(direction.y(), direction.x());
    osg::Quat zRot(zAngle, osg::Vec3d(0,0,1));

    osg::Vec3d yAxis = zRot * osg::Vec3d(0,1,0);
    double zLength = (direction - osg::Vec3d(0,0,direction.z())).length();
    double yAngle = - atan2(direction.z(), zLength) + osg::PI/2;
    osg::Quat yRot(yAngle, yAxis);

    return zRot * yRot;
}
