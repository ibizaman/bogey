#include "TexturingGeode.h"
#include <osg/StateSet>
#include <osgDB/ReadFile>
#include "exception/ErrorOpeningFileException.h"

void TexturingGeode::setTexture(Texture* texture, unsigned int unit)
{
    getOrCreateStateSet()->setTextureAttributeAndModes(unit, texture);
}

void TexturingGeode::loadImageInTexture(Texture* texture, const std::string& file) {
    osg::Image* image = osgDB::readImageFile(file);
    if (!image) {
        throw ErrorOpeningFileException(file);
    }
    texture->setImage(image);
}
