#ifndef FACEFACTORY_H
#define FACEFACTORY_H

#include <osg/Referenced>
#include <osg/Vec3d>
#include <osg/ref_ptr>
#include "lib/DirectionMap.hxx"
#include "object/Face.h"

class FaceFactory : public osg::Referenced
{
public:
    typedef DirectionMap<Face> FaceMap;
    typedef FaceMap::Direction Direction;
    typedef FaceMap::Element Element;

    FaceFactory();
    Element get(const Direction&);
    const FaceMap& getMap();

private:
    FaceMap _faces;
};

#endif
