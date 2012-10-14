#ifndef TEXTUREDDRAWABLE_H
#define TEXTUREDDRAWABLE_H

#include <osg/Geometry>
#include <list>

class TexturedDrawable : public osg::Geometry
{
public:
    void init();

protected:
    typedef osg::ref_ptr<osg::Vec4Array> Vertices;
    typedef osg::ref_ptr<osg::DrawElementsUInt> Element;
    typedef std::list<Element> ElementsList;
    typedef osg::ref_ptr<osg::Vec2Array> TextureCoords;

protected:
    virtual void createVertices(Vertices&) = 0;
    virtual void createElements(ElementsList&) = 0;
    virtual void createTextureCoords(TextureCoords&) = 0;
};

#endif

