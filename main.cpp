#include <osg/Fog>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/Node>
#include <osg/PolygonMode>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>
#include <osgGA/NodeTrackerManipulator>
#include "callback/PlayerAnimationCallback.h"
#include "factory/ShapeFactory.h"
#include "handler/InputEventHandler.h"
#include "state/PlayerState.h"
#include "transform/ShapeTransform.h"
#include "transform/PlayerTransform.h"
#include "object/Cube.h"
#include "shape/Chunk.h"
#include "lib/TexturingGroup.h"
#include "lib/Perlin3D.h"

#ifdef DEBUG
#include <osgViewer/ViewerEventHandlers>
#endif

#if defined TEST
#include <gmock/gmock.h>
#endif

osg::ref_ptr<osg::Geometry> createAxis(const osg::Vec3&, const osg::Vec4&);

int main(int argc, char* argv[])
{
#if defined TEST

    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();

#else

    (void) argc;
    (void) argv;
    srand(time(NULL));

    // Factories
    // ---------
    osg::ref_ptr<ShapeFactory> shapeFactory(new ShapeFactory());
    shapeFactory->insert("cube", new Cube(1, shapeFactory));
    
    // Graph
    // -----
    ShapeFactory::Element playerCube(shapeFactory->get("cube"));
    ShapeFactory::Element terrainCube(shapeFactory->get("cube"));
    ShapeFactory::Element cube1(shapeFactory->get("cube"));
    cube1->setPosition(osg::Vec3d(2,3,0));
    //ShapeFactory::Element cube2(shapeFactory->get("cube"));
    //cube2->setPosition(osg::Vec3d(3,3,0));
    ShapeFactory::Element cube3(shapeFactory->get("cube"));
    cube3->setPosition(osg::Vec3d(4,3,0));
    cube3->setAttitude(osg::Quat(osg::PI/2, osg::Vec3d(1,0,0)));
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
    osg::ref_ptr<osg::Group> root(new osg::Group);
    osg::ref_ptr<TexturingGroup> cobbleGroup(new TexturingGroup("texture/cobblestone.tga"));
    osg::ref_ptr<TexturingGroup> woodGroup(new TexturingGroup("texture/wood.tga"));
    osg::ref_ptr<TexturingGroup> sandGroup(new TexturingGroup("texture/sand.tga"));
    osg::ref_ptr<TexturingGroup> plankGroup(new TexturingGroup("texture/plank.tga"));
    osg::ref_ptr<TexturingGroup> dirtGroup(new TexturingGroup("texture/dirt.tga"));
    root->addChild(cobbleGroup);
    root->addChild(woodGroup);
    root->addChild(sandGroup);
    root->addChild(plankGroup);
    root->addChild(dirtGroup);

    cobbleGroup->addChild(playerTransform);

    osg::ref_ptr<osg::PositionAttitudeTransform> terrainTransform(new osg::PositionAttitudeTransform());
    terrainTransform->addChild(terrainCube);
    terrainTransform->setPosition(osg::Vec3d(0,0,-20));
    terrainTransform->setScale(osg::Vec3d(1000,1000,1));
    cobbleGroup->addChild(terrainTransform);

    woodGroup->addChild(cube1);
    //woodGroup->addChild(cube2);
    woodGroup->addChild(cube3);

    Perlin3D perlin1(123456789 , 10000000 , 0.5);
    osg::ref_ptr<Chunk> chunk1(new Chunk(shapeFactory->get("cube"), perlin1));
    plankGroup->addChild(chunk1);

    // Axis
    // ----
    osg::ref_ptr<osg::Geode> axis(new osg::Geode());
    axis->addDrawable(createAxis(osg::Vec3(1,0,0), osg::Vec4(1,0,0,1)));
    axis->addDrawable(createAxis(osg::Vec3(0,1,0), osg::Vec4(0,1,0,1)));
    axis->addDrawable(createAxis(osg::Vec3(0,0,1), osg::Vec4(0,0,1,1)));
    root->addChild(axis);

    // Fog & Lightning
    // ---------------
    osg::ref_ptr<osg::StateSet> ss = root->getOrCreateStateSet();

    ss->setMode(GL_LIGHTING, osg::StateAttribute::ON);

    const osg::Vec4 fogColor(0.796, 0.996, 0.996, 1.0);
    osg::ref_ptr<osg::Fog> fog(new osg::Fog());
    fog->setMode(osg::Fog::LINEAR);
    fog->setColor(fogColor);
    fog->setStart(15);
    fog->setEnd(100);
    // ss->setAttributeAndModes(fog);

    osg::ref_ptr<osg::Light> light(new osg::Light());
    light->setLightNum(0);
    light->setDiffuse(osg::Vec4d(0.5,0.5,0.5,1));
    light->setAmbient(osg::Vec4d(0.5,0.5,0.5,1));
    light->setQuadraticAttenuation(0.001);
    light->setPosition(osg::Vec4d(0,0,0,1));

    osg::ref_ptr<osg::LightSource> lightsource = new osg::LightSource();
    lightsource->setLight(light);
    lightsource->setStateSetModes(*root->getOrCreateStateSet(), osg::StateAttribute::ON);
    root->addChild(lightsource);

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

osg::ref_ptr<osg::Geometry> createAxis(const osg::Vec3& direction, const osg::Vec4& color)
{
    osg::ref_ptr<osg::Geometry> axis(new osg::Geometry);
    osg::ref_ptr<osg::Vec3Array> vertices(new osg::Vec3Array);
    vertices->push_back(osg::Vec3(0,0,0));
    vertices->push_back(direction);
    axis->setVertexArray(vertices);

    osg::ref_ptr<osg::Vec4Array> colors(new osg::Vec4Array);
    colors->push_back(color);
    axis->setColorArray(colors);
    axis->setColorBinding(osg::Geometry::BIND_OVERALL);

    axis->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,0,vertices->size()));

    return axis;
}
