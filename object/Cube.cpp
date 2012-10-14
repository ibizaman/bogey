#include "Cube.h"
#include <osgDB/ReadFile>
#include "exception/ErrorOpeningFileException.h"

Cube::Cube() 
    : TexturingGeode()
{
    _faces[Face::TOP]    = new Face(Face::TOP);
    _faces[Face::BOTTOM] = new Face(Face::BOTTOM);
    _faces[Face::FRONT]  = new Face(Face::FRONT);
    _faces[Face::BACK]   = new Face(Face::BACK);
    _faces[Face::LEFT]   = new Face(Face::LEFT);
    _faces[Face::RIGHT]  = new Face(Face::RIGHT);

    for (Faces::iterator it = _faces.begin(); it != _faces.end(); ++it) {
        addDrawable(it->second);
    }
    init();
}

void Cube::createTexture(Texture& texture)
{
    texture->setDataVariance(osg::Object::DYNAMIC);
    texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::NEAREST);
    texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::NEAREST);
    texture->setWrap( osg::Texture::WRAP_R, osg::Texture::REPEAT );

    setImageFromFile(texture, "texture/wood.tga");
}
