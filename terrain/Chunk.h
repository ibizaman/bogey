#ifndef CHUNK_H
#define CHUNK_H

#include <osg/PositionAttitudeTransform>
#include "terrain/ShapeTransform.h"
#include "lib/Perlin3D.h"

class Chunk : public osg::PositionAttitudeTransform
{
public:
    typedef osg::ref_ptr<ShapeTransform> Shape;

    Chunk(Shape element, const Perlin3D&);
};

#endif
