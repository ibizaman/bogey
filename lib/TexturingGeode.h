#ifndef TEXTURINGGEODE_H
#define TEXTURINGGEODE_H

#include <osg/Geode>
#include <osg/Texture2D>
#include <string>

class TexturingGeode : public osg::Geode
{
public:
    void init();

protected:
    typedef osg::ref_ptr<osg::Texture2D> Texture;

protected:
    virtual void createTexture(Texture&) = 0;
    void setImageFromFile(Texture&, const std::string&);
};

#endif
