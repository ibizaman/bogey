#ifndef TEXTURINGGROUP_H
#define TEXTURINGGROUP_H

#include <osg/Group>
#include <osg/Texture2D>
#include <osg/ref_ptr>
#include <string>

class TexturingGroup : public osg::Group
{
public:
    typedef osg::ref_ptr<osg::Texture2D> Texture;

    TexturingGroup();
    TexturingGroup(const std::string&, unsigned int unit = 0);
    void setTexture(Texture, unsigned int unit = 0);
    void setTexture(const std::string&, unsigned int unit = 0);
    void loadImageInTexture(Texture, const std::string&);
};

#endif
