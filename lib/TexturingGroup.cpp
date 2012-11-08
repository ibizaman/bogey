#include "TexturingGroup.h"
#include <osg/StateSet>
#include <osgDB/ReadFile>
#include "exception/ErrorOpeningFileException.h"

TexturingGroup::TexturingGroup()
    : osg::Group()
{
}

TexturingGroup::TexturingGroup(const std::string& file, unsigned int unit)
    : osg::Group()
{
    setTexture(file, unit);
}

void TexturingGroup::setTexture(Texture texture, unsigned int unit)
{
    getOrCreateStateSet()->setTextureAttributeAndModes(unit, texture);
}

void TexturingGroup::setTexture(const std::string& file, unsigned int unit)
{
    Texture texture(new osg::Texture2D());
    loadImageInTexture(texture, file);
    setTexture(texture, unit);
}

void TexturingGroup::loadImageInTexture(Texture texture, const std::string& file)
{
    osg::Image* image = osgDB::readImageFile(file);
    if (!image) {
        throw ErrorOpeningFileException(file);
    }
    texture->setImage(image);
}
