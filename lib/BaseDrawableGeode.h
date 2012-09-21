#ifndef BASEDRAWABLEGEODE_H
#define BASEDRAWABLEGEODE_H

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <string>
#include <list>

class BaseDrawableGeode : public osg::Geode
{
public:
    BaseDrawableGeode(int, const std::string&);
    virtual void init();

protected:
    struct Texture {
        osg::ref_ptr<osg::Texture2D> texture2D;
        std::string uniform;
    };

protected:
    typedef osg::ref_ptr<osg::Program> Program;
    typedef osg::ref_ptr<osg::Vec4Array> Vertices;
    typedef osg::ref_ptr<osg::DrawElementsUInt> Element;
    typedef std::list<Element> ElementsList;
    typedef std::list<Texture> TexturesList;

protected:
    virtual void createVertices(Vertices&) = 0;
    virtual void createElements(ElementsList&) = 0;
    virtual void createShader(Program&) = 0;
    virtual void createTextures(TexturesList&) = 0;

private:
    int _attribLocation;
    std::string _attrib;
};

#endif
