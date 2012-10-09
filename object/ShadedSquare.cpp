#include "ShadedSquare.h"
#include "callback/UpdateTimerCallback.h"

#include <osgDB/ReadFile>

ShadedSquare::ShadedSquare(const std::string& vertexShader, const std::string& fragmentShader)
    : BaseDrawableGeode(0, "position"),
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
    BaseDrawableGeode::init();
    createTimer(getOrCreateStateSet());
}

void ShadedSquare::createVertices(Vertices& vertices)
{
    vertices->push_back(osg::Vec4(-2,-1.5, 0, 1));
    vertices->push_back(osg::Vec4(-2, 1.5, 0, 1));
    vertices->push_back(osg::Vec4( 2,-1.5, 0, 1));
    vertices->push_back(osg::Vec4( 2, 1.5, 0, 1));
}

void ShadedSquare::createElements(ElementsList& elements)
{
    Element surface(new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_STRIP, 0));
    surface->push_back(0);
    surface->push_back(1);
    surface->push_back(2);
    surface->push_back(3);
    elements.push_back(surface);
}

/**
 * Creates shaders used for blending texture
 */
void ShadedSquare::createShader(Program& program)
{
    osg::ref_ptr<osg::Shader> vertex_shader(new osg::Shader(osg::Shader::VERTEX));
    vertex_shader->loadShaderSourceFromFile(_vertexShader);

    osg::ref_ptr<osg::Shader> fragment_shader(new osg::Shader(osg::Shader::FRAGMENT));
    fragment_shader->loadShaderSourceFromFile(_fragmentShader);

    program->setName(_vertexShader);
    program->addShader(vertex_shader);
    program->addShader(fragment_shader);
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
void ShadedSquare::createTextures(TexturesList& textures)
{
    Texture hello1;
    hello1.uniform = "texture0";
    hello1.texture2D = new osg::Texture2D();
    hello1.texture2D->setDataVariance(osg::Object::DYNAMIC);
    hello1.texture2D->setImage(osgDB::readImageFile("texture/hello1.tga"));

    Texture hello2;
    hello2.uniform = "texture1";
    hello2.texture2D = new osg::Texture2D();
    hello2.texture2D->setDataVariance(osg::Object::DYNAMIC);
    hello2.texture2D->setImage(osgDB::readImageFile("texture/hello2.tga"));

    textures.push_back(hello1);
    textures.push_back(hello2);
}
