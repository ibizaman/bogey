#include "TexturingGeode.h"
#include <osg/StateSet>
#include <osgDB/ReadFile>
#include "exception/ErrorOpeningFileException.h"

void TexturingGeode::init() {
    Texture texture(new osg::Texture2D());
    createTexture(texture);
    getOrCreateStateSet()->setTextureAttributeAndModes(0, texture);
}

void TexturingGeode::setImageFromFile(Texture& texture, const std::string& file) {
    osg::Image* face = osgDB::readImageFile(file);
    if (!face) {
        throw ErrorOpeningFileException(file);
    }
    texture->setImage(face);
}
