#include "ShapeFactory.h"
#include <osg/Geode>

ShapeFactory::ShapeFactory()
{
    _cubeDirections.push_back(osg::Vec3d( 1, 0, 0));
    _cubeDirections.push_back(osg::Vec3d(-1, 0, 0));
    _cubeDirections.push_back(osg::Vec3d( 0, 1, 0));
    _cubeDirections.push_back(osg::Vec3d( 0,-1, 0));
    _cubeDirections.push_back(osg::Vec3d( 0, 0, 1));
    _cubeDirections.push_back(osg::Vec3d( 0, 0,-1));
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

ShapeFactory::PAT ShapeFactory::getCube(const osg::Vec3d& position, const osg::Quat& attitude, double size)
{
    PAT cube(new osg::PositionAttitudeTransform());
    cube->setPosition(position);
    cube->setAttitude(attitude);

    const double ratio = 1.0/6.0;

    int textureNum = 0;
    for (Directions::iterator direction = _cubeDirections.begin(); direction != _cubeDirections.end(); ++direction) {

        osg::ref_ptr<TexturedDrawable> drawable(getSquare(osg::Vec2d(textureNum*ratio, 0), osg::Vec2d(ratio, 1), size));

        // should be neighbour geode
        osg::ref_ptr<osg::Geode> geode(new osg::Geode());
        geode->addDrawable(drawable);

        PAT face(getTranslatedPAT(*direction, size/2));
        face->addChild(geode);

        cube->addChild(face);

        ++textureNum;
    }

    return cube;
}

ShapeFactory::PAT ShapeFactory::getTranslatedPAT(osg::Vec3d direction, double shift)
{
    direction.normalize();

    PAT pat(new osg::PositionAttitudeTransform());
    pat->setPosition(direction*shift);

    osg::Quat attitude;
    attitude.makeRotate(direction, osg::Vec3d(0,0,1));
    pat->setAttitude(attitude);

    return pat;
}
