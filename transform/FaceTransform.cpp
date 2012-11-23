#include "FaceTransform.h"
#include <osg/Geode>

FaceTransform::FaceTransform(Drawable drawable)
{
    osg::ref_ptr<osg::Geode> geode(new osg::Geode());
    geode->addDrawable(drawable);
    addChild(geode);
}
