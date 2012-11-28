#ifndef SHAPETRANSFORM_H
#define SHAPETRANSFORM_H

#include <osg/PositionAttitudeTransform>
#include <osg/Node>
#include <osg/ref_ptr>
#include <osg/Referenced>
#include <osg/BoundingBox>
#include "lib/DirectionMap.hxx"

class ShapeTransform : public osg::PositionAttitudeTransform
{
public:
    typedef osg::ref_ptr<osg::PositionAttitudeTransform> Face;
    typedef osg::observer_ptr<ShapeTransform> Neighbour;
    typedef DirectionMap<osg::PositionAttitudeTransform> Faces;

    ShapeTransform();
    ShapeTransform(osg::ref_ptr<Faces>);
    ShapeTransform(const ShapeTransform&);
    void bindNeighbour(Neighbour);
    void unbindNeighbour(const Faces::Direction&);
    void setTransparence(bool);
    bool isTransparent() const;
    bool isFaceHidden(const Faces::Direction&);
    Neighbour getNeighbour(const Faces::Direction&);
    void setBoundingBox(const osg::BoundingBox&);
    osg::BoundingBox getBoundingBox() const;

protected:
    void init(osg::ref_ptr<Faces>);

private:
    bool hideFace(const Faces::Direction&);
    bool showFace(const Faces::Direction&);

    Faces::Direction getDirection(Neighbour);
    struct Tuple : public osg::Referenced{
        Tuple(Face);
        Face face;
        Neighbour neighbour;
    };

    bool _transparent;
    typedef DirectionMap<Tuple> TupleMap;
    TupleMap _directionMap;
    osg::BoundingBox _box;
};

#endif
