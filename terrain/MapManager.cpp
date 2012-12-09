#include "MapManager.h"

#include <osg/Fog>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/PositionAttitudeTransform>
#include <osg/StateSet>
#include <osgDB/FileNameUtils>
#include <osgDB/FileUtils>
#include <osgGA/NodeTrackerManipulator>
#include "player/BodyAnimationCallback.h"
#include "player/BodyTransform.h"
#include "player/InputEventHandler.h"
#include "terrain/Cube.h"
#include "terrain/ShapeTransform.h"
#include "lib/Perlin3D.h"

MapManager::MapManager(const std::string& mapsDirectory, const std::string& texturesDirectory)
    : _mapsPath(mapsDirectory),
      _texturesPath(texturesDirectory),
      _texturingGroups(new TexturingGroups(true)),
      _shapes(new ShapeFactory())
{
    _shapes->insert("cube", new Cube(1, _shapes));

    _player = _shapes->getOriginal("cube");
}

void MapManager::loadMap(const std::string& map, osg::ref_ptr<osgViewer::Viewer> viewer, osg::ref_ptr<osg::Group> root)
{
    std::string file = _mapsPath;
    file += map;
    (void) file;

    initTexturingGroups(root);
    initLightning(root);
    initFog(root, viewer);
    initPlayer(viewer);
    initManipulator(viewer);
    initMap();
}

void MapManager::initTexturingGroups(osg::ref_ptr<osg::Group> root)
{
    osgDB::DirectoryContents textures = osgDB::getDirectoryContents(_texturesPath);
    for (osgDB::DirectoryContents::const_iterator texture = textures.begin(); texture != textures.end(); ++texture) {
        std::string name = osgDB::getNameLessExtension(*texture);
        std::string extension = osgDB::getFileExtension(*texture);
        std::string path = osgDB::concatPaths(_texturesPath, *texture);
        if (extension == "tga" && *texture != "." && *texture != "..") {
            _texturingGroups->insert(name, new TexturingGroup(path));
            root->addChild(_texturingGroups->getOriginal(name));
        }
    }
}

void MapManager::initLightning(osg::ref_ptr<osg::Group> root)
{
    osg::ref_ptr<osg::StateSet> ss = root->getOrCreateStateSet();

    ss->setMode(GL_LIGHTING, osg::StateAttribute::ON);

    osg::ref_ptr<osg::Light> light(new osg::Light());
    light->setLightNum(0);
    light->setDiffuse(osg::Vec4d(0.5,0.5,0.5,1));
    light->setAmbient(osg::Vec4d(0.5,0.5,0.5,1));
    light->setQuadraticAttenuation(0.005);
    light->setPosition(osg::Vec4d(0,0,0,1));

    osg::ref_ptr<osg::LightSource> lightsource = new osg::LightSource();
    lightsource->setLight(light);
    lightsource->setStateSetModes(*ss, osg::StateAttribute::ON);
    root->addChild(lightsource);
}

void MapManager::initFog(osg::ref_ptr<osg::Group> root, osg::ref_ptr<osgViewer::Viewer> viewer)
{
    osg::ref_ptr<osg::StateSet> ss = root->getOrCreateStateSet();

    const osg::Vec4 fogColor(0.796, 0.996, 0.996, 1.0);
    osg::ref_ptr<osg::Fog> fog(new osg::Fog());
    fog->setMode(osg::Fog::LINEAR);
    fog->setColor(fogColor);
    fog->setStart(15);
    fog->setEnd(100);
    // ss->setAttributeAndModes(fog);
    viewer->getCamera()->setClearColor(fogColor);
}

void MapManager::initPlayer(osg::ref_ptr<osgViewer::Viewer> viewer)
{
    osg::ref_ptr<BodyTransform> playerTransform(new BodyTransform());
    playerTransform->addChild(_player);
    playerTransform->setPosition(osg::Vec3d(-10,0,0));

    osg::ref_ptr<KeyboardState> keyboardState(new KeyboardState());
    playerTransform->addUpdateCallback(new BodyAnimationCallback(keyboardState));

    _texturingGroups->getOriginal("cobblestone")->addChild(playerTransform);

    viewer->addEventHandler(new InputEventHandler(keyboardState));
}

void MapManager::initManipulator(osg::ref_ptr<osgViewer::Viewer> viewer)
{
    osg::ref_ptr<osgGA::NodeTrackerManipulator> manipulator(new osgGA::NodeTrackerManipulator());
    manipulator->setTrackNode(_player);
    manipulator->setHomePosition(
            osg::Vec3d(-10.0, 0.0, 10.0),
            osg::Vec3d(0.0, 0.0, 7.0),
            osg::Vec3d(0.0, 0.0, 1.0)
        );
    viewer->setCameraManipulator(manipulator);

    // Disable and center cursor
    viewer->realize();
    osgViewer::Viewer::Windows windows;
    viewer->getWindows(windows);
    for (osgViewer::Viewer::Windows::iterator window = windows.begin(); window != windows.end(); ++window) {
        (*window)->useCursor(false);
        int x,y,width,height;
        (*window)->getWindowRectangle(x, y, width, height);
        viewer->requestWarpPointer(x + width/2, y + height/2);
    }
}

void MapManager::initMap()
{
    Perlin3D perlin1(123456789 , 10000000 , 0.5);

    osg::ref_ptr<Chunk> chunk1(new Chunk(_shapes->getOriginal("cube"), perlin1));
    _chunks.push_back(chunk1);

    osg::ref_ptr<Chunk> chunk2(new Chunk(_shapes->getOriginal("cube"), perlin1));
    chunk2->setPosition(osg::Vec3(16,0,0));
    _chunks.push_back(chunk2);

    _texturingGroups->getOriginal("wood")->addChild(chunk1);
    _texturingGroups->getOriginal("sand")->addChild(chunk2);
}

void MapManager::setMapsPath(const std::string& path)
{
    _mapsPath = path;
}
