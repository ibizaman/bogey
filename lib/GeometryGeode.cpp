#include "GeometryGeode.h"
#include <osg/StateSet>
#include <osg/Geometry>

void GeometryGeode::init() {
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
