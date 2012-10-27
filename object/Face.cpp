#include "Face.h"

Face::Face(Direction direction)
    : TexturedDrawable()
{
    float x = 1.0;

    Vertices* vertices = new Vertices();
    switch (direction) {
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

    setVertices(vertices);

    Element* surface = new Element(osg::PrimitiveSet::TRIANGLE_STRIP, 0);
    surface->push_back(0);
    surface->push_back(1);
    surface->push_back(2);
    surface->push_back(3);
    addElement(surface);

    TextureCoords* textureCoords = new TextureCoords();
    switch (direction) {
        case FRONT:
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

    setTextureCoords(textureCoords);
}
