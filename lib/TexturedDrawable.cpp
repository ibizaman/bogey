#include "TexturedDrawable.h"
#include <osg/StateSet>

TexturedDrawable::TexturedDrawable()
{
    getOrCreateVertexBufferObject()->setUsage(GL_STATIC_DRAW);
    setUseDisplayList(false);
    setUseVertexBufferObjects(true);
}

void TexturedDrawable::setVertices(Vertices* vertices)
{
    setVertexArray(vertices);
}

void TexturedDrawable::addElement(Element* element)
{
    addPrimitiveSet(element);
}

void TexturedDrawable::setTextureCoords(TextureCoords* textureCoords, unsigned int unit)
{
    setTexCoordArray(unit, textureCoords);
}

