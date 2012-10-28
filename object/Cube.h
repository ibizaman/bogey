#ifndef CUBE_H
#define CUBE_H

#include "lib/TexturingGeode.h"
#include "lib/DirectionMap.hxx"
#include "factory/FaceFactory.h"
#include <map>
#include "object/Face.h"

class Cube : public TexturingGeode
{
public:
    Cube(osg::ref_ptr<FaceFactory>);

private:
    typedef DirectionMap<Face> FaceMap;
    FaceMap _faces;
};

#endif
