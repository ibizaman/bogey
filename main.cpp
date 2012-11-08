#include <osg/Fog>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Node>
#include <osg/PolygonMode>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>
#include <osgGA/NodeTrackerManipulator>
#include "factory/ShapeFactory.h"
#include "handler/InputEventHandler.h"
#include "transform/CubeTransform.h"
#include "state/PlayerState.h"
#include "transform/PlayerTransform.h"
#include "callback/PlayerAnimationCallback.h"
#include "lib/TexturingGroup.h"

#ifdef DEBUG
#include <osgViewer/ViewerEventHandlers>
#endif

#if defined TEST
#include <gmock/gmock.h>
#endif

int main(int argc, char* argv[])
{
#if defined TEST

    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();

#else

    (void) argc;
    (void) argv;

    // Factories
    // ---------
    osg::ref_ptr<ShapeFactory> shapeFactory(new ShapeFactory());
    osg::ref_ptr<TexturingGroup> woodGroup(new TexturingGroup());
    
    // Graph
    // -----
    osg::ref_ptr<CubeTransform> playerCube(shapeFactory->getCube(osg::Vec3d(0,0,0), osg::Quat(), 1));
    osg::ref_ptr<CubeTransform> terrainCube(shapeFactory->getCube(osg::Vec3d(0,0,0), osg::Quat(), 1));
    osg::ref_ptr<CubeTransform> cube1(shapeFactory->getCube(osg::Vec3d(2,3,0), osg::Quat(), 1));
    //osg::ref_ptr<CubeTransform> cube2(shapeFactory->getCube(osg::Vec3d(3,3,0), osg::Quat(), 1));
    osg::ref_ptr<CubeTransform> cube3(shapeFactory->getCube(osg::Vec3d(4,3,0), osg::Quat(osg::PI/2, osg::Vec3d(1,0,0)), 1));
    //cube1->bindNeighbour(cube2);
    //cube2->bindNeighbour(cube3);
    cube1->bindNeighbour(cube3);

    // Player
    // ------
    osg::ref_ptr<PlayerTransform> playerTransform(new PlayerTransform());
    playerTransform->addChild(playerCube);
    playerTransform->setPosition(osg::Vec3d(-10,0,0));
    osg::ref_ptr<PlayerState> playerState(new PlayerState());
    playerTransform->addUpdateCallback(new PlayerAnimationCallback(playerState));

    // Terrain
    // -------
    osg::ref_ptr<osg::PositionAttitudeTransform> terrainTransform(new osg::PositionAttitudeTransform());
    terrainTransform->addChild(terrainCube);
    terrainTransform->setPosition(osg::Vec3d(0,0,-2));
    terrainTransform->setScale(osg::Vec3d(1000,1000,1));

    osg::ref_ptr<TexturingGroup> root(new TexturingGroup("texture/wood.tga"));
    root->addChild(terrainTransform);
    root->addChild(playerTransform);
    root->addChild(cube1);
    //root->addChild(cube2);
    root->addChild(cube3);

    // Fog & Lightning
    // ---------------
    osg::ref_ptr<osg::StateSet> ss = root->getOrCreateStateSet();

    ss->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    const osg::Vec4 fogColor(0.796, 0.996, 0.996, 1.0);
    osg::ref_ptr<osg::Fog> fog(new osg::Fog());
    fog->setMode(osg::Fog::LINEAR);
    fog->setColor(fogColor);
    fog->setStart(15);
    fog->setEnd(100);
    // ss->setAttributeAndModes(fog);

    // Viewer
    // ------
    osg::ref_ptr<osgViewer::Viewer> viewer(new osgViewer::Viewer());

    // Camera & manipulator
    osg::ref_ptr<osgGA::NodeTrackerManipulator> manipulator(new osgGA::NodeTrackerManipulator());
    manipulator->setTrackNode(playerCube);
    manipulator->setHomePosition(
            osg::Vec3d(-10.0, 0.0, 10.0),
            osg::Vec3d(0.0, 0.0, 7.0),
            osg::Vec3d(0.0, 0.0, 1.0)
        );
    viewer->setCameraManipulator(manipulator);
    viewer->getCamera()->setClearColor(fogColor);

    // Disable cursor
    viewer->realize();
    osgViewer::Viewer::Windows windows;
    viewer->getWindows(windows);
    for (osgViewer::Viewer::Windows::iterator window = windows.begin(); window != windows.end(); ++window) {
        (*window)->useCursor(false);
        int x,y,width,height;
        (*window)->getWindowRectangle(x, y, width, height);
        viewer->requestWarpPointer(x + width/2, y + height/2);
    }

    // Handlers
    viewer->addEventHandler(new InputEventHandler(playerState));
#ifdef DEBUG
    osg::ref_ptr<osgViewer::StatsHandler> statEvent(new osgViewer::StatsHandler());
    statEvent->setKeyEventTogglesOnScreenStats('p');
    viewer->addEventHandler(statEvent);
#endif

    viewer->setSceneData(root);

    viewer->run();
#endif
}

