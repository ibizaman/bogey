#include "GameManager.h"

#ifdef DEBUG
#include <osgViewer/ViewerEventHandlers>
#endif

GameManager::GameManager()
    : _mapManager(new MapManager("terrain/maps/", "terrain/texture/")),
      _viewer(new osgViewer::Viewer()),
      _root(new osg::Group()),
      _shapeFactory(new ShapeFactory())
{

    beginGame("map1");
}

void GameManager::beginGame(const std::string& map)
{
    _mapManager->loadMap(map, _viewer, _root);

#ifdef DEBUG
    osg::ref_ptr<osgViewer::StatsHandler> statEvent(new osgViewer::StatsHandler());
    statEvent->setKeyEventTogglesOnScreenStats('p');
    _viewer->addEventHandler(statEvent);
#endif

    _viewer->setSceneData(_root);
    _viewer->run();
}
