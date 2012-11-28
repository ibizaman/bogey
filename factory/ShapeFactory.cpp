#include "ShapeFactory.h"
#include "transform/FaceTransform.h"
#include <cmath>

ShapeFactory::ShapeFactory(bool notErasable)
    : Factory<ShapeTransform>(notErasable)
{
}

ShapeFactory::Drawable ShapeFactory::getSquare(const osg::Vec2d& pos, const osg::Vec2d& size, double length)
{
    Drawable square(new TexturedDrawable());

    TexturedDrawable::Vertices* vertices = new TexturedDrawable::Vertices();
    vertices->push_back(osg::Vec4( length/2,-length/2, 0, 1));
    vertices->push_back(osg::Vec4(-length/2,-length/2, 0, 1));
    vertices->push_back(osg::Vec4( length/2, length/2, 0, 1));
    vertices->push_back(osg::Vec4(-length/2, length/2, 0, 1));
    square->setVertices(vertices);

    TexturedDrawable::Element* element = new TexturedDrawable::Element(osg::PrimitiveSet::TRIANGLE_STRIP, 0);
    element->push_back(0);
    element->push_back(1);
    element->push_back(2);
    element->push_back(3);
    square->addElement(element);

    TexturedDrawable::TextureCoords* texture = new TexturedDrawable::TextureCoords();
    texture->push_back(osg::Vec2d(pos.x(),          pos.y()         ));
    texture->push_back(osg::Vec2d(pos.x(),          pos.y()+size.y()));
    texture->push_back(osg::Vec2d(pos.x()+size.x(), pos.y()         ));
    texture->push_back(osg::Vec2d(pos.x()+size.x(), pos.y()+size.y()));
    square->setTextureCoords(texture);

    return square;
}

void ShapeFactory::translate(osg::PositionAttitudeTransform* face, osg::Vec3d direction, double shift)
{
    direction.normalize();

    double zAngle = atan2(direction.y(), direction.x());
    osg::Quat zRot(zAngle, osg::Vec3d(0,0,1));

    osg::Vec3d yAxis = zRot * osg::Vec3d(0,1,0);
    double zLength = (direction - osg::Vec3d(0,0,direction.z())).length();
    double yAngle = - atan2(direction.z(), zLength) + osg::PI/2;
    osg::Quat yRot(yAngle, yAxis);

    face->setAttitude(zRot * yRot);
    face->setPosition(direction*shift);
}
