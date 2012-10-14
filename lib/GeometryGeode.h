#ifndef GEOMETRYGEODE_H
#define GEOMETRYGEODE_H

#include <osg/Geode>
#include <osg/Texture2D>
#include <list>

class GeometryGeode : public osg::Geode
{
public:
    void init();

protected:
    struct Texture {
        osg::ref_ptr<osg::Texture2D> texture2D;
        osg::ref_ptr<osg::Vec2Array> coords;
    };
    typedef osg::ref_ptr<osg::Vec4Array> Vertices;
    typedef osg::ref_ptr<osg::DrawElementsUInt> Element;
    typedef std::list<Element> ElementsList;

protected:
    virtual void createVertices(Vertices&) = 0;
    virtual void createElements(ElementsList&) = 0;
    virtual void createTexture(Texture&) = 0;
};

#endif
