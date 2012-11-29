#ifndef FACETRANSFORM_H
#define FACETRANSFORM_H

#include <osg/PositionAttitudeTransform>
#include <osg/ref_ptr>
#include "lib/TexturedDrawable.h"

class FaceTransform : public osg::PositionAttitudeTransform
{
public:
    typedef osg::ref_ptr<TexturedDrawable> Drawable;

    FaceTransform(Drawable);
    void setDirectionAndShift(const osg::Vec3d&, double shift);

protected:
    Drawable _drawable;
    osg::Quat computeQuat(osg::Vec3d direction);
};

#endif
