#ifndef TEXTUREDDRAWABLE_H
#define TEXTUREDDRAWABLE_H

#include <osg/Geometry>
#include <list>

class TexturedDrawable : public osg::Geometry
{
public:
    typedef osg::Vec3Array Vertices;
    typedef osg::DrawElementsUInt Element;
    typedef osg::Vec2Array TextureCoords;
    typedef osg::Vec3Array Normals;
    typedef Normals::iterator normalsIterator;

    TexturedDrawable();
    void setVertices(Vertices*);
    void addElement(Element*);
    void setTextureCoords(TextureCoords*, unsigned int = 0);
    void setNormals(Normals*);

    normalsIterator normalsBegin();
    normalsIterator normalsEnd();

private:
    osg::ref_ptr<Normals> _normals;
};

#endif
