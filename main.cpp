#include <osg/Fog>
#include <osg/Group>
#include <osg/Geode>
#include <osg/PolygonMode>
#include <osg/MatrixTransform>
#include <osgViewer/Viewer>
#include <osgGA/NodeTrackerManipulator>
#include "object/ShadedSquare.h"
#include "lib/KeyboardEventHandler.h"

#ifdef DEBUG
#include <osgViewer/ViewerEventHandlers>
#endif

int main(int argc, char* argv[])
{
    // Graph
    // -----
    std::string vertexShader = argc >= 2 ? argv[1] : "shader/hello.vert";
    std::string fragmentShader = "shader/hello.frag";
    osg::ref_ptr<ShadedSquare> hello(new ShadedSquare(vertexShader, fragmentShader));
    hello->init();

    osg::ref_ptr<osg::MatrixTransform> cameraTransform(new osg::MatrixTransform());
    cameraTransform->addChild(hello);

    osg::ref_ptr<osg::Group> root(new osg::Group());
    root->addChild(hello);
    root->addChild(cameraTransform);

    // Fog & Lightning
    // ---------------
    osg::ref_ptr<osg::StateSet> ss = root->getOrCreateStateSet();

    ss->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    const osg::Vec4 fogColor(0.5, 0.5, 1, 1.0);
    osg::ref_ptr<osg::Fog> fog(new osg::Fog());
    fog->setMode(osg::Fog::LINEAR);
    fog->setColor(fogColor);
    fog->setStart(15);
    fog->setEnd(100);
    ss->setAttributeAndModes(fog);

    // Viewer
    // ------
    osg::ref_ptr<osgViewer::Viewer> viewer(new osgViewer::Viewer());

    // Camera & manipulator
    osg::ref_ptr<osgGA::NodeTrackerManipulator> manipulator(new osgGA::NodeTrackerManipulator());
    manipulator->setTrackNode(hello);
    manipulator->setHomePosition(
            osg::Vec3d(0.0, 0.0, 10.0),
            osg::Vec3d(0.0, 0.0, 0.0),
            osg::Vec3d(0.0, 1.0, 0.0)
        );
    viewer->setCameraManipulator(manipulator);
    viewer->getCamera()->setClearColor(fogColor);

    // Handlers
    viewer->addEventHandler(new KeyboardEventHandler(cameraTransform));
#ifdef DEBUG
    osg::ref_ptr<osgViewer::StatsHandler> statEvent(new osgViewer::StatsHandler());
    statEvent->setKeyEventTogglesOnScreenStats('p');
    viewer->addEventHandler(statEvent);
#endif

    viewer->setSceneData(root);

    viewer->run();
}

