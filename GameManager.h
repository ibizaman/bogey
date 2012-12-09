#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <osg/ref_ptr>
#include <osg/Group>
#include <osgViewer/Viewer>
#include "terrain/MapManager.h"
#include "terrain/ShapeFactory.h"

class GameManager
{
public:
    GameManager();
    void beginGame(const std::string&);

private:
    osg::ref_ptr<MapManager> _mapManager;
    osg::ref_ptr<osgViewer::Viewer> _viewer;
    osg::ref_ptr<osg::Group> _root;
    osg::ref_ptr<ShapeFactory> _shapeFactory;
};

#endif
