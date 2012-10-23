#include <osg/Fog>
#include <osg/Group>
#include <osg/Geode>
#include <osg/PolygonMode>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>
#include <osgGA/NodeTrackerManipulator>
#include "handler/InputEventHandler.h"
#include "state/PlayerState.h"
#include "transform/PlayerTransform.h"
#include "callback/PlayerAnimationCallback.h"
#include "lib/Cube.h"
#include "shapes/Rectangle.h"
#include "shapes/Circle.h"

#ifdef DEBUG
#include <osgViewer/ViewerEventHandlers>
#endif

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;
    
    // Graph
    // -----
    osg::ref_ptr<Cube> cube(new Cube("sand"));

    // Player
    // ------
    osg::ref_ptr<PlayerTransform> playerTransform(new PlayerTransform());
    playerTransform->addChild(cube);
    playerTransform->setPosition(osg::Vec3d(-10,0,0));
    osg::ref_ptr<PlayerState> playerState(new PlayerState());
    playerTransform->addUpdateCallback(new PlayerAnimationCallback(playerState));

    // Terrain
    // -------
    // osg::ref_ptr<Rectangle> rectangle(new Rectangle("wood" , 5 , 5 , osg::Vec3d(0 , 0 , -2)));
    osg::ref_ptr<Circle> circle(new Circle("sand" , 15 , osg::Vec3d(0,0,-20)));
    osg::ref_ptr<osg::Group> root(new osg::Group());
    root->addChild(playerTransform);
    // root->addChild(rectangle);
    root->addChild(circle);

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
    manipulator->setTrackNode(cube);
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
}

