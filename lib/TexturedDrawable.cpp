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

void TexturedDrawable::setNormals(Normals* normals)
{
    setNormalArray(normals);
    setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
}

TexturedDrawable::normalsIterator TexturedDrawable::normalsBegin()
{
    return dynamic_cast<osg::Vec3Array*>(getNormalArray())->begin();
}

TexturedDrawable::normalsIterator TexturedDrawable::normalsEnd()
{
    return dynamic_cast<osg::Vec3Array*>(getNormalArray())->end();
}
