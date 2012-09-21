#include "BaseDrawableGeode.h"

BaseDrawableGeode::BaseDrawableGeode(int attribLocation, const std::string& attrib)
    : osg::Geode(),
      _attribLocation(attribLocation),
      _attrib(attrib)
{
}

void BaseDrawableGeode::init()
{
    osg::ref_ptr<osg::Geometry> geometry(new osg::Geometry());

    // set VBO usage
    geometry->getOrCreateVertexBufferObject()->setUsage(GL_STATIC_DRAW);
    geometry->setUseDisplayList(false);
    geometry->setUseVertexBufferObjects(true);

    // vertices
    osg::ref_ptr<osg::Vec4Array> vertices(new osg::Vec4Array());
    createVertices(vertices);
    geometry->setVertexAttribArray(_attribLocation, vertices);
    geometry->setVertexAttribBinding(_attribLocation, osg::Geometry::BIND_PER_VERTEX);

    // elements
    ElementsList elements;
    createElements(elements);
    for (ElementsList::iterator elem = elements.begin(); elem != elements.end(); ++elem) {
        geometry->addPrimitiveSet(*elem);
    }

    // shaders
    osg::ref_ptr<osg::Program> program(new osg::Program);
    createShader(program);
    program->addBindAttribLocation(_attrib, _attribLocation);
    getOrCreateStateSet()->setAttributeAndModes(program);

    // textures
    TexturesList textures;
    createTextures(textures);
    int i = 0;
    for (TexturesList::iterator tex = textures.begin(); tex != textures.end(); ++tex) {
        getOrCreateStateSet()->setTextureAttributeAndModes(i, tex->texture2D);
        getOrCreateStateSet()->addUniform(new osg::Uniform(tex->uniform.c_str(), i));
        ++i;
    }

    addDrawable(geometry);
}
