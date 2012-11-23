#ifndef SHAPETRANSFORM_H
#define SHAPETRANSFORM_H

#include <osg/PositionAttitudeTransform>
#include <osg/Node>
#include <osg/ref_ptr>
#include <osg/Referenced>
#include "lib/DirectionMap.hxx"

class ShapeTransform : public osg::PositionAttitudeTransform
{
public:
    typedef osg::ref_ptr<osg::PositionAttitudeTransform> Face;
    typedef osg::observer_ptr<ShapeTransform> Neighbour;
    typedef DirectionMap<osg::PositionAttitudeTransform> Faces;

    ShapeTransform(osg::ref_ptr<Faces>);
    void bindNeighbour(Neighbour);
    void unbindNeighbour(const Faces::Direction&);
    void setTransparence(bool);
    bool isTransparent() const;
    bool isFaceHidden(const Faces::Direction&);
    Neighbour getNeighbour(const Faces::Direction&);

private:
    bool hideFace(const Faces::Direction&);
    bool showFace(const Faces::Direction&);

    Faces::Direction getDirection(Neighbour);
    struct Tuple : public osg::Referenced{
        Tuple(Face);
        Face face;
        Neighbour neighbour;
    };

    typedef DirectionMap<Tuple> TupleMap;
    TupleMap _directionMap;
    bool _transparent;
};

#endif
