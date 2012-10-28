#include "Cube.h"
#include <osgDB/ReadFile>
#include "exception/ErrorOpeningFileException.h"

Cube::Cube(osg::ref_ptr<FaceFactory> faceFactory) 
    : TexturingGeode(),
      _faces(faceFactory->getMap())
{
    for (FaceMap::iterator it = _faces.begin(); it != _faces.end(); ++it) {
        addDrawable(it->second);
    }

    Texture* texture = new Texture();
    texture->setDataVariance(osg::Object::DYNAMIC);
    texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::NEAREST);
    texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::NEAREST);
    texture->setWrap( osg::Texture::WRAP_R, osg::Texture::REPEAT );

    loadImageInTexture(texture, "texture/wood.tga");
    setTexture(texture);
}
