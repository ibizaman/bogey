#ifndef SHADEDSQUARE_H
#define SHADEDSQUARE_H

#include <osg/Geometry>
#include <osg/Geode>
#include <string>

class ShadedSquare : public osg::Geode
{
public:
    ShadedSquare(const std::string&, const std::string&);

    void setVertexShader(const std::string&);
    void setFragmentShader(const std::string&);

protected:
    virtual ~ShadedSquare();

    void init();
    void createVertices(osg::ref_ptr<osg::Geometry>);
    void createShader(osg::ref_ptr<osg::StateSet>);
    void createTimer(osg::ref_ptr<osg::StateSet>);
    void createTextures(osg::ref_ptr<osg::StateSet>);

    int _attribLocation;
    std::string _vertexShader;
    std::string _fragmentShader;
};

#endif
