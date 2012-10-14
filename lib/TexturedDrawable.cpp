#include "TexturedDrawable.h"
#include <osg/StateSet>

void TexturedDrawable::init()
{
    // set VBO usage
    getOrCreateVertexBufferObject()->setUsage(GL_STATIC_DRAW);
    setUseDisplayList(false);
    setUseVertexBufferObjects(true);

    // vertices
    Vertices vertices(new osg::Vec4Array());
    createVertices(vertices);
    setVertexArray(vertices);

    // elements
    ElementsList elements;
    createElements(elements);
    for (ElementsList::iterator elem = elements.begin(); elem != elements.end(); ++elem) {
        addPrimitiveSet(*elem);
    }

    // texture coordinates
    TextureCoords textureCoords(new osg::Vec2Array());
    createTextureCoords(textureCoords);
    setTexCoordArray(0, textureCoords);
}

