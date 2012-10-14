#include "Face.h"

Face::Face(Direction direction)
    : _direction(direction)
{
    init();
}

void Face::createVertices(Vertices& vertices)
{
    float x = 1.0;

    switch (_direction) {
        case FRONT:
            vertices->push_back(osg::Vec4(-x,-x, x, 1));
            vertices->push_back(osg::Vec4(-x, x, x, 1));
            vertices->push_back(osg::Vec4( x,-x, x, 1));
            vertices->push_back(osg::Vec4( x, x, x, 1));
            break;
        case BACK:
            vertices->push_back(osg::Vec4(-x,-x,-x, 1));
            vertices->push_back(osg::Vec4(-x, x,-x, 1));
            vertices->push_back(osg::Vec4( x,-x,-x, 1));
            vertices->push_back(osg::Vec4( x, x,-x, 1));
            break;
        case LEFT:
            vertices->push_back(osg::Vec4(-x,-x,-x, 1));
            vertices->push_back(osg::Vec4(-x, x,-x, 1));
            vertices->push_back(osg::Vec4(-x,-x, x, 1));
            vertices->push_back(osg::Vec4(-x, x, x, 1));
            break;
        case RIGHT:
            vertices->push_back(osg::Vec4( x,-x, x, 1));
            vertices->push_back(osg::Vec4( x, x, x, 1));
            vertices->push_back(osg::Vec4( x,-x,-x, 1));
            vertices->push_back(osg::Vec4( x, x,-x, 1));
            break;
        case TOP:
            vertices->push_back(osg::Vec4(-x, x, x, 1));
            vertices->push_back(osg::Vec4(-x, x,-x, 1));
            vertices->push_back(osg::Vec4( x, x, x, 1));
            vertices->push_back(osg::Vec4( x, x,-x, 1));
            break;
        case BOTTOM:
            vertices->push_back(osg::Vec4(-x,-x,-x, 1));
            vertices->push_back(osg::Vec4(-x,-x, x, 1));
            vertices->push_back(osg::Vec4( x,-x,-x, 1));
            vertices->push_back(osg::Vec4( x,-x, x, 1));
            break;
    }
}

void Face::createElements(ElementsList& elements)
{
    Element surface(new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_STRIP, 0));
    surface->push_back(0);
    surface->push_back(1);
    surface->push_back(2);
    surface->push_back(3);
    elements.push_back(surface);
}

void Face::createTextureCoords(TextureCoords& textureCoords)
{
    switch (_direction) {
        case FRONT:
            textureCoords = new osg::Vec2Array;
            textureCoords->push_back(osg::Vec2(0.0f, 0.5f));
            textureCoords->push_back(osg::Vec2(0.0f, 1.0f));
            textureCoords->push_back(osg::Vec2(0.5f, 0.5f));
            textureCoords->push_back(osg::Vec2(0.5f, 1.0f));
            break;
        case BACK:
            textureCoords->push_back(osg::Vec2(0.0f, 0.5f));
            textureCoords->push_back(osg::Vec2(0.0f, 1.0f));
            textureCoords->push_back(osg::Vec2(0.5f, 0.5f));
            textureCoords->push_back(osg::Vec2(0.5f, 1.0f));
            break;
        case LEFT:
            textureCoords->push_back(osg::Vec2(0.0f, 0.5f));
            textureCoords->push_back(osg::Vec2(0.0f, 1.0f));
            textureCoords->push_back(osg::Vec2(0.5f, 0.5f));
            textureCoords->push_back(osg::Vec2(0.5f, 1.0f));
            break;
        case RIGHT:
            textureCoords->push_back(osg::Vec2(0.0f, 0.5f));
            textureCoords->push_back(osg::Vec2(0.0f, 1.0f));
            textureCoords->push_back(osg::Vec2(0.5f, 0.5f));
            textureCoords->push_back(osg::Vec2(0.5f, 1.0f));
            break;
        case TOP:
            textureCoords->push_back(osg::Vec2(0.5f, 0.5f));
            textureCoords->push_back(osg::Vec2(0.5f, 1.0f));
            textureCoords->push_back(osg::Vec2(1.0f, 0.5f));
            textureCoords->push_back(osg::Vec2(1.0f, 1.0f));
            break;
        case BOTTOM:
            textureCoords->push_back(osg::Vec2(0.5f, 0.5f));
            textureCoords->push_back(osg::Vec2(0.5f, 1.0f));
            textureCoords->push_back(osg::Vec2(1.0f, 0.5f));
            textureCoords->push_back(osg::Vec2(1.0f, 1.0f));
            break;
    }
}
