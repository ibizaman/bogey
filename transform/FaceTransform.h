#ifndef FACETRANSFORM_H
#define FACETRANSFORM_H

#include <osg/PositionAttitudeTransform>
#include <osg/ref_ptr>
#include <osg/Drawable>

class FaceTransform : public osg::PositionAttitudeTransform
{
public:
    typedef osg::ref_ptr<osg::Drawable> Drawable;

    FaceTransform(Drawable);
};

#endif
