#ifndef CUBE_H
#define CUBE_H

#include <list>
#include <osg/Geode>
#include <osg/Texture2D>

class Cube : public osg::Geode
{
public:
    Cube();
    void init();

protected:
    struct Texture {
        osg::ref_ptr<osg::Texture2D> texture2D;
        osg::ref_ptr<osg::Vec2Array> coords;
    };

protected:
    typedef osg::ref_ptr<osg::Vec4Array> Vertices;
    typedef osg::ref_ptr<osg::DrawElementsUInt> Element;
    typedef std::list<Element> ElementsList;

protected:
    void createVertices(Vertices&);
    void createElements(ElementsList&);
    void createTexture(Texture&);

private:
    int _attribLocation;
};

#endif
