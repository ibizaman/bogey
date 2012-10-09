#include <osg/Fog>
#include <osg/Group>
#include <osg/Geode>
#include <osg/PolygonMode>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>
#include <osgGA/NodeTrackerManipulator>
#include "object/ShadedSquare.h"
#include "handler/InputEventHandler.h"
#include "state/PlayerState.h"
#include "transform/PlayerTransform.h"
#include "callback/PlayerAnimationCallback.h"

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

    // Player
    // ------
    osg::ref_ptr<PlayerTransform> playerTransform(new PlayerTransform());
    playerTransform->addChild(hello);
    playerTransform->setPosition(osg::Vec3d(1,0,0));
    osg::ref_ptr<PlayerState> playerState(new PlayerState());
    playerTransform->addUpdateCallback(new PlayerAnimationCallback(playerState));

    // Terrain
    // -------
    osg::ref_ptr<osg::PositionAttitudeTransform> terrainTransform(new osg::PositionAttitudeTransform());
    terrainTransform->addChild(hello);
    terrainTransform->setPosition(osg::Vec3d(0,0,-1));
    terrainTransform->setScale(osg::Vec3d(10,10,1));

    osg::ref_ptr<osg::Group> root(new osg::Group());
    root->addChild(terrainTransform);
    root->addChild(playerTransform);

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
    viewer->addEventHandler(new InputEventHandler(playerState));
#ifdef DEBUG
    osg::ref_ptr<osgViewer::StatsHandler> statEvent(new osgViewer::StatsHandler());
    statEvent->setKeyEventTogglesOnScreenStats('p');
    viewer->addEventHandler(statEvent);
#endif

    viewer->setSceneData(root);

    viewer->run();
}

