#include "ShapeFactory.h"
#include "terrain/FaceTransform.h"
#include <cmath>

ShapeFactory::ShapeFactory(bool notErasable)
    : Factory<ShapeTransform>(notErasable)
{
}

ShapeFactory::Drawable ShapeFactory::getSquare(const osg::Vec2d& pos, const osg::Vec2d& size, double length)
{
    Drawable square(new TexturedDrawable());

    TexturedDrawable::Vertices* vertices = new TexturedDrawable::Vertices();
    vertices->push_back(osg::Vec3( length/2,-length/2, 0));
    vertices->push_back(osg::Vec3( length/2, length/2, 0));
    vertices->push_back(osg::Vec3(-length/2,-length/2, 0));
    vertices->push_back(osg::Vec3(-length/2, length/2, 0));
    square->setVertices(vertices);

    TexturedDrawable::Element* element = new TexturedDrawable::Element(osg::PrimitiveSet::TRIANGLE_STRIP, 0);
    element->push_back(0);
    element->push_back(1);
    element->push_back(2);
    element->push_back(3);
    square->addElement(element);

    TexturedDrawable::TextureCoords* texture = new TexturedDrawable::TextureCoords();
    texture->push_back(osg::Vec2d(pos.x(),          pos.y()         ));
    texture->push_back(osg::Vec2d(pos.x()+size.x(), pos.y()         ));
    texture->push_back(osg::Vec2d(pos.x(),          pos.y()+size.y()));
    texture->push_back(osg::Vec2d(pos.x()+size.x(), pos.y()+size.y()));
    square->setTextureCoords(texture);

    TexturedDrawable::Normals* normals = new TexturedDrawable::Normals();
    normals->push_back(osg::Vec3(0,0,1));
    normals->push_back(osg::Vec3(0,0,1));
    normals->push_back(osg::Vec3(0,0,1));
    normals->push_back(osg::Vec3(0,0,1));
    square->setNormals(normals);

    return square;
}
