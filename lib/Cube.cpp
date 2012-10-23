#include "Cube.h"
#include <osg/Geometry>
#include <osg/StateSet>
#include <osgDB/ReadFile>
#include "exception/ErrorOpeningFileException.h"

Cube::Cube(std::string name) 
    : osg::Geode() , _name(name)
{
    init();
}

void Cube::init()
{
    osg::ref_ptr<osg::Geometry> geometry(new osg::Geometry());

    // set VBO usage
    geometry->getOrCreateVertexBufferObject()->setUsage(GL_STATIC_DRAW);
    geometry->setUseDisplayList(false);
    geometry->setUseVertexBufferObjects(true);

    // vertices
    Vertices vertices(new osg::Vec4Array());
    createVertices(vertices);
    geometry->setVertexArray(vertices);

    // elements
    ElementsList elements;
    createElements(elements);
    for (ElementsList::iterator elem = elements.begin(); elem != elements.end(); ++elem) {
        geometry->addPrimitiveSet(*elem);
    }

    // textures
    Texture texture;
    createTexture(texture);
    geometry->setTexCoordArray(0, texture.coords);
    getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.texture2D);

    addDrawable(geometry);

}

void Cube::createVertices(Vertices& vertices)
{
    float x = 1.0;
    // front side
    vertices->push_back(osg::Vec4(-x,-x, x, 1));
    vertices->push_back(osg::Vec4(-x, x, x, 1));
    vertices->push_back(osg::Vec4( x,-x, x, 1));
    vertices->push_back(osg::Vec4( x, x, x, 1));
    // back side    
    vertices->push_back(osg::Vec4(-x,-x,-x, 1));
    vertices->push_back(osg::Vec4(-x, x,-x, 1));
    vertices->push_back(osg::Vec4( x,-x,-x, 1));
    vertices->push_back(osg::Vec4( x, x,-x, 1));
    // left side    
    vertices->push_back(osg::Vec4(-x,-x,-x, 1));
    vertices->push_back(osg::Vec4(-x, x,-x, 1));
    vertices->push_back(osg::Vec4(-x,-x, x, 1));
    vertices->push_back(osg::Vec4(-x, x, x, 1));
    // right side
    vertices->push_back(osg::Vec4( x,-x, x, 1));
    vertices->push_back(osg::Vec4( x, x, x, 1));
    vertices->push_back(osg::Vec4( x,-x,-x, 1));
    vertices->push_back(osg::Vec4( x, x,-x, 1));
    // up side
    vertices->push_back(osg::Vec4(-x, x, x, 1));
    vertices->push_back(osg::Vec4(-x, x,-x, 1));
    vertices->push_back(osg::Vec4( x, x, x, 1));
    vertices->push_back(osg::Vec4( x, x,-x, 1));
    // down side
    vertices->push_back(osg::Vec4(-x,-x,-x, 1));
    vertices->push_back(osg::Vec4(-x,-x, x, 1));
    vertices->push_back(osg::Vec4( x,-x,-x, 1));
    vertices->push_back(osg::Vec4( x,-x, x, 1));
}

void Cube::createElements(ElementsList& elements)
{
    Element surface0(new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_STRIP, 0));
    surface0->push_back(0);
    surface0->push_back(1);
    surface0->push_back(2);
    surface0->push_back(3);
    elements.push_back(surface0);

    Element surface1(new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_STRIP, 0));
    surface1->push_back(4);
    surface1->push_back(5);
    surface1->push_back(6);
    surface1->push_back(7);
    elements.push_back(surface1);
    
    Element surface2(new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_STRIP, 0));
    surface2->push_back(8);
    surface2->push_back(9);
    surface2->push_back(10);
    surface2->push_back(11);
    elements.push_back(surface2);
    
    Element surface3(new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_STRIP, 0));
    surface3->push_back(12);
    surface3->push_back(13);
    surface3->push_back(14);
    surface3->push_back(15);
    elements.push_back(surface3);
    
    Element surface4(new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_STRIP, 0));
    surface4->push_back(16);
    surface4->push_back(17);
    surface4->push_back(18);
    surface4->push_back(19);
    elements.push_back(surface4);
    
    Element surface5(new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_STRIP, 0));
    surface5->push_back(20);
    surface5->push_back(21);
    surface5->push_back(22);
    surface5->push_back(23);
    elements.push_back(surface5);
}

void Cube::createTexture(Texture& texture)
{
    texture.texture2D = new osg::Texture2D();
    texture.texture2D->setDataVariance(osg::Object::DYNAMIC);
    texture.texture2D->setFilter(osg::Texture::MIN_FILTER, osg::Texture::NEAREST);
    texture.texture2D->setFilter(osg::Texture::MAG_FILTER, osg::Texture::NEAREST);
    texture.texture2D->setWrap( osg::Texture::WRAP_R, osg::Texture::REPEAT );
    
    std::string texLocalisation = "texture/" + _name + ".tga";
    osg::Image* face = osgDB::readImageFile(texLocalisation);
    if (!face) {
        throw ErrorOpeningFileException(texLocalisation);
    }
    texture.texture2D->setImage(face);
    if(face->getImageSizeInBytes() <= 16*16*4) {
        texture.coords = new osg::Vec2Array;
        for(int i = 1 ; i <= 6 ; i++) {
            texture.coords->push_back(osg::Vec2(0.0f, 0.0f));
            texture.coords->push_back(osg::Vec2(0.0f, 1.0f));
            texture.coords->push_back(osg::Vec2(1.0f, 0.0f));
            texture.coords->push_back(osg::Vec2(1.0f, 1.0f));
        }
    }
    
    else {
        float LD , LU , RD , RU;
        LD = LU = 0.0;
        RD = RU = 1.0/6.0; 
        texture.coords = new osg::Vec2Array;
        for (int i = 1 ; i <= 6 ; i++) {
            texture.coords->push_back(osg::Vec2(LD, 0.0f));
            texture.coords->push_back(osg::Vec2(LU, 1.0f));
            texture.coords->push_back(osg::Vec2(RD, 0.0f));
            texture.coords->push_back(osg::Vec2(RU, 1.0f));
            
            LD += 1.0/6.0;
            LU += 1.0/6.0;
            RD += 1.0/6.0;
            RU += 1.0/6.0;
        }
    }
}
