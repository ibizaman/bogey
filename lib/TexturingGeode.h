#ifndef TEXTURINGGEODE_H
#define TEXTURINGGEODE_H

#include <osg/Geode>
#include <osg/Texture2D>
#include <string>

class TexturingGeode : public osg::Geode
{
public:
    typedef osg::Texture2D Texture;

    void setTexture(Texture*, unsigned int unit = 0);
    void loadImageInTexture(Texture*, const std::string&);
};

#endif
