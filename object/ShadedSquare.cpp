#include "ShadedSquare.h"
#include "lib/UpdateTimerCallback.h"

#include <osg/Texture2D>
#include <osgDB/ReadFile>

ShadedSquare::ShadedSquare(const std::string& vertexShader, const std::string& fragmentShader) :
    _attribLocation(0),
    _vertexShader(vertexShader),
    _fragmentShader(fragmentShader)
{
    init();
}

ShadedSquare::~ShadedSquare()
{
}

void ShadedSquare::init()
{
    osg::ref_ptr<osg::Geometry> geometry(new osg::Geometry());

    // set VBO usage
    geometry->getOrCreateVertexBufferObject()->setUsage(GL_STATIC_DRAW);
    geometry->setUseDisplayList(false);
    geometry->setUseVertexBufferObjects(true);

    createVertices(geometry);

    osg::ref_ptr<osg::StateSet> state = getOrCreateStateSet();
    createShader(state);

    createTimer(state);
    createTextures(state);

    addDrawable(geometry);
}

void ShadedSquare::createVertices(osg::ref_ptr<osg::Geometry> geometry)
{
    // add vertices
    osg::ref_ptr<osg::Vec4Array> vertices(new osg::Vec4Array());
    vertices->push_back(osg::Vec4(0, 0, 0, 1));
    vertices->push_back(osg::Vec4(0, 1, 0, 1));
    vertices->push_back(osg::Vec4(1, 0, 0, 1));
    vertices->push_back(osg::Vec4(1, 1, 0, 1));

    // add elements
    osg::ref_ptr<osg::DrawElementsUInt> surface(new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_STRIP, 0));
    surface->push_back(0);
    surface->push_back(1);
    surface->push_back(2);
    surface->push_back(3);
    geometry->addPrimitiveSet(surface);

    geometry->setVertexAttribArray(_attribLocation, vertices);
    geometry->setVertexAttribBinding(_attribLocation, osg::Geometry::BIND_PER_VERTEX);
}

/**
 * Creates shaders used for blending texture
 */
void ShadedSquare::createShader(osg::ref_ptr<osg::StateSet> state)
{
    osg::ref_ptr<osg::Shader> vertex_shader(new osg::Shader(osg::Shader::VERTEX));
    vertex_shader->loadShaderSourceFromFile(_vertexShader);

    osg::ref_ptr<osg::Shader> fragment_shader(new osg::Shader(osg::Shader::FRAGMENT));
    fragment_shader->loadShaderSourceFromFile(_fragmentShader);

    osg::ref_ptr<osg::Program> program(new osg::Program);
    program->setName(_vertexShader);
    program->addShader(vertex_shader);
    program->addShader(fragment_shader);

    program->addBindAttribLocation("position", _attribLocation);

    state->setAttributeAndModes(program);
}

/**
 * Creates timer and sets associated callback
 */
void ShadedSquare::createTimer(osg::ref_ptr<osg::StateSet> state)
{
    osg::ref_ptr<osg::Uniform> timer(new osg::Uniform("timer", 0.0f));
    timer->setUpdateCallback(new UpdateTimerCallback());
    state->addUniform(timer);
}

/**
 * Creates hello1 and hello2 textures use for blending
 */
void ShadedSquare::createTextures(osg::ref_ptr<osg::StateSet> state)
{
    // create texture and uniform related to hello1.tga
    osg::ref_ptr<osg::Texture2D> hello1_texture(new osg::Texture2D());
    hello1_texture->setDataVariance(osg::Object::DYNAMIC);
    hello1_texture->setImage(osgDB::readImageFile("texture/hello1.tga"));
    state->setTextureAttributeAndModes(0, hello1_texture);

    osg::ref_ptr<osg::Uniform> hello1_uniform(new osg::Uniform("texture0", 0));
    state->addUniform(hello1_uniform);

    // create texture and uniform related to hello2.tga
    osg::ref_ptr<osg::Texture2D> hello2_texture(new osg::Texture2D());
    hello2_texture->setDataVariance(osg::Object::DYNAMIC);
    hello2_texture->setImage(osgDB::readImageFile("texture/hello2.tga"));
    state->setTextureAttributeAndModes(1, hello2_texture);

    osg::ref_ptr<osg::Uniform> hello2_uniform(new osg::Uniform("texture1", 1));
    state->addUniform(hello2_uniform);
}
