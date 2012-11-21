#ifndef CHUNK_H
#define CHUNK_H

#include <osg/Geode>
#include <osg/PositionAttitudeTransform>
#include <string>
#include "lib/Perlin3D.h"
#include "lib/Cube.h"

class Chunk : public osg::PositionAttitudeTransform
{
    
public:
    
    Chunk(std::string type , osg::Vec3d GPos , Perlin3D perlin);
    void create(); 
    
private:
    
    const std::string _type;
    const osg::Vec3d _GPos;
    double _chunk[16][16][16];
};

#endif