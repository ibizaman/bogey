#include "FaceFactory.h"

FaceFactory::FaceFactory()
{
    _faces.set(osg::Vec3d( 0, 0, 1), new Face(Face::TOP));
    _faces.set(osg::Vec3d( 0, 0,-1), new Face(Face::BOTTOM));
    _faces.set(osg::Vec3d( 0, 1, 0), new Face(Face::BACK));
    _faces.set(osg::Vec3d( 0,-1, 0), new Face(Face::FRONT));
    _faces.set(osg::Vec3d( 1, 0, 0), new Face(Face::RIGHT));
    _faces.set(osg::Vec3d(-1, 0, 0), new Face(Face::LEFT));
}

FaceFactory::Element FaceFactory::get(const Direction& direction)
{
    return _faces.get(direction);
}

const FaceFactory::FaceMap& FaceFactory::getMap()
{
    return _faces;
}
