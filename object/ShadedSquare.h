#ifndef SHADEDSQUARE_H
#define SHADEDSQUARE_H

#include <string>
#include <osg/ref_ptr>
#include <osg/StateSet>
#include "lib/BaseDrawableGeode.h"

class ShadedSquare : public BaseDrawableGeode
{
public:
    ShadedSquare(const std::string&, const std::string&);
    virtual void init();

protected:
    virtual ~ShadedSquare();

    virtual void createVertices(Vertices&);
    virtual void createElements(ElementsList&);
    virtual void createShader(Program&);
    virtual void createTextures(TexturesList&);
    void createTimer(osg::ref_ptr<osg::StateSet>);

    std::string _vertexShader;
    std::string _fragmentShader;
};

#endif
