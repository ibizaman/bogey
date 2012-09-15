#include <osg/Fog>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Node>
#include <osg/PolygonMode>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <string>
#include <iostream>

osg::ref_ptr<osg::Geode> getShadedSquareNode(const std::string&);

class UpdateTimer : public osg::Uniform::Callback
{
public:
    virtual void operator()(osg::Uniform* uniform, osg::NodeVisitor* nv)
    {
        uniform->set((float)nv->getFrameStamp()->getSimulationTime());
    }
};

int main(int argc, char* argv[])
{
    const osg::Vec4 fogColor(0.5, 0.5, 1, 1.0);

    osg::ref_ptr<osg::Group> root(new osg::Group());
    root->addChild(getShadedSquareNode(argc >= 2 ? argv[1] : "shader/hello.vert"));

    osg::ref_ptr<osg::StateSet> ss = root->getOrCreateStateSet();

    ss->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    osg::ref_ptr<osg::Fog> fog(new osg::Fog());
    fog->setMode(osg::Fog::LINEAR);
    fog->setColor(fogColor);
    fog->setStart(15);
    fog->setEnd(100);
    ss->setAttributeAndModes(fog);

    osgViewer::Viewer viewer;
    viewer.setSceneData(root);
    viewer.getCamera()->setClearColor(fogColor);

    viewer.run();
}

osg::ref_ptr<osg::Geode> getShadedSquareNode(const std::string& vertex_shader_file)
{
    osg::ref_ptr<osg::Geometry> geometry(new osg::Geometry());
    osg::ref_ptr<osg::StateSet> state(geometry->getOrCreateStateSet());

    // add vertices
    osg::ref_ptr<osg::VertexBufferObject> vbo(geometry->getOrCreateVertexBufferObject());
    vbo->setUsage(GL_STATIC_DRAW);

    geometry->setUseDisplayList(false);
    geometry->setUseVertexBufferObjects(true);

    osg::ref_ptr<osg::Vec4Array> vertices(new osg::Vec4Array());
    vertices->push_back(osg::Vec4(0, 0, 0, 1));
    vertices->push_back(osg::Vec4(0, 0, 1, 1));
    vertices->push_back(osg::Vec4(1, 0, 0, 1));
    vertices->push_back(osg::Vec4(1, 0, 1, 1));

    // add elements
    osg::ref_ptr<osg::DrawElementsUInt> surface(new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_STRIP, 0));
    surface->push_back(0);
    surface->push_back(1);
    surface->push_back(2);
    surface->push_back(3);
    geometry->addPrimitiveSet(surface);

    // create shader
    osg::ref_ptr<osg::Shader> vertex_shader(new osg::Shader(osg::Shader::VERTEX));
    vertex_shader->loadShaderSourceFromFile(vertex_shader_file);

    osg::ref_ptr<osg::Shader> fragment_shader(new osg::Shader(osg::Shader::FRAGMENT));
    fragment_shader->loadShaderSourceFromFile("shader/hello.frag");

    osg::ref_ptr<osg::Program> program(new osg::Program);
    program->setName(vertex_shader_file);
    program->addShader(vertex_shader);
    program->addShader(fragment_shader);

    int attrib_loc = 0;
    program->addBindAttribLocation("position", attrib_loc);

    geometry->setVertexAttribArray(attrib_loc, vertices);
    geometry->setVertexAttribBinding(attrib_loc, osg::Geometry::BIND_PER_VERTEX);

    state->setAttributeAndModes(program);

    // create timer uniform
    osg::ref_ptr<osg::Uniform> timer(new osg::Uniform("timer", 0.0f));
    timer->setUpdateCallback(new UpdateTimer());
    state->addUniform(timer);

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

    // create geode container
    osg::ref_ptr<osg::Geode> geode(new osg::Geode());
    geode->addDrawable(geometry);

    return geode;
}

