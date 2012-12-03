#include "ShapeTransform.h"

ShapeTransform::ShapeTransform()
    : osg::PositionAttitudeTransform(),
      _transparent(false)
{
}

ShapeTransform::ShapeTransform(osg::ref_ptr<Faces> faces)
    : osg::PositionAttitudeTransform(),
      _transparent(false)
{
    init(faces);
}

ShapeTransform::ShapeTransform(const ShapeTransform& other)
    : osg::PositionAttitudeTransform(other),
      _transparent(other._transparent),
      _directionMap(other._directionMap),
      _box(other._box)
{
}

void ShapeTransform::init(osg::ref_ptr<Faces> faces)
{
    for (Faces::iterator face = faces->begin(); face != faces->end(); ++face) {
        _directionMap.set(face->first, new Tuple(face->second));
        addChild(face->second);
    }
}

void ShapeTransform::bindNeighbour(Neighbour newNeighbour)
{
    if (newNeighbour.valid()) {
        Faces::Direction direction = getDirection(newNeighbour);
        Neighbour oldNeighbour = _directionMap.get(direction)->neighbour;

        if (newNeighbour.valid() && newNeighbour.get() != this && newNeighbour != oldNeighbour) {
            if (oldNeighbour.valid()) {
                unbindNeighbour(direction);
            }
            if (isTransparent() || newNeighbour->isTransparent()) {
                showFace(direction);
            } else {
                hideFace(direction);
            }
            _directionMap.get(direction)->neighbour = newNeighbour;
            newNeighbour->bindNeighbour(this);
        }
    }
}

void ShapeTransform::unbindNeighbour(const Faces::Direction& direction)
{
    TupleMap::iterator tupleIt = _directionMap.find(direction);
    if (tupleIt != _directionMap.end()) {

        showFace(direction);

        Neighbour oldNeighbour = tupleIt->second->neighbour;
        if (oldNeighbour.valid()) {
            _directionMap.get(direction)->neighbour = 0;
            oldNeighbour->unbindNeighbour(-direction);
        }

    }
}

void ShapeTransform::setTransparence(bool transparent)
{
    _transparent = transparent;
    for (TupleMap::iterator tupleIt = _directionMap.begin(); tupleIt != _directionMap.end(); ++tupleIt) {
        Neighbour neighbour = tupleIt->second->neighbour;
        if (neighbour.valid()) {
            if (isTransparent() || neighbour->isTransparent()) {
                showFace(tupleIt->first);
                neighbour->showFace(-tupleIt->first);
            } else {
                hideFace(tupleIt->first);
                neighbour->hideFace(-tupleIt->first);
            }
        }
    }
}

bool ShapeTransform::isTransparent() const
{
    return _transparent;
}

bool ShapeTransform::hideFace(const Faces::Direction& direction)
{
    return removeChild(_directionMap.get(direction)->face);
}

bool ShapeTransform::showFace(const Faces::Direction& direction)
{
    if (!isFaceHidden(direction)) {
        return false;
    } else {
        return addChild(_directionMap.get(direction)->face);
    }
}

bool ShapeTransform::isFaceHidden(const Faces::Direction& direction)
{
    return !containsNode(_directionMap.get(direction)->face);
}

ShapeTransform::Faces::Direction ShapeTransform::getDirection(Neighbour neighbour)
{
    return neighbour->getPosition() - getPosition();
}

ShapeTransform::Neighbour ShapeTransform::getNeighbour(const Faces::Direction& direction)
{
    return _directionMap.get(direction)->neighbour;
}

void ShapeTransform::setBoundingBox(const osg::BoundingBox& box)
{
    _box = box;
}

osg::BoundingBox ShapeTransform::getBoundingBox() const
{
    return _box;
}

ShapeTransform::Tuple::Tuple(Face face)
    :face(face)
{
}
