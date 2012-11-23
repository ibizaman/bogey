#ifndef TEXTUREDDRAWABLE_H
#define TEXTUREDDRAWABLE_H

#include <osg/Geometry>
#include <list>

class TexturedDrawable : public osg::Geometry
{
public:
    typedef osg::Vec4Array Vertices;
    typedef osg::DrawElementsUInt Element;
    typedef osg::Vec2Array TextureCoords;

    TexturedDrawable();
    void setVertices(Vertices*);
    void addElement(Element*);
    void setTextureCoords(TextureCoords*, unsigned int = 0);
};

#endif
