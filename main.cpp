#include <osg/Fog>
#include <osg/Group>
#include <osg/Geode>
#include <osg/PolygonMode>
#include <osgViewer/Viewer>
#include "object/ShadedSquare.h"

int main(int argc, char* argv[])
{
    const osg::Vec4 fogColor(0.5, 0.5, 1, 1.0);

    std::string vertexShader = argc >= 2 ? argv[1] : "shader/hello.vert";
    std::string fragmentShader = "shader/hello.frag";
    osg::ref_ptr<osg::Geode> hello(new ShadedSquare(vertexShader, fragmentShader));

    osg::ref_ptr<osg::Group> root(new osg::Group());
    root->addChild(hello);

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

