#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <list>
#include <map>
#include <string>
#include <osg/ref_ptr>
#include <osg/Group>
#include <osg/Referenced>
#include <osgViewer/Viewer>
#include "terrain/Chunk.h"
#include "terrain/ShapeFactory.h"
#include "lib/Factory.hxx"
#include "lib/TexturingGroup.h"

class MapManager : public osg::Referenced
{
public:
    MapManager(const std::string&, const std::string&);
    void loadMap(const std::string&, osg::ref_ptr<osgViewer::Viewer>, osg::ref_ptr<osg::Group>);
    void setMapsPath(const std::string&);

private:
    void initTexturingGroups(osg::ref_ptr<osg::Group>);
    void initLightning(osg::ref_ptr<osg::Group>);
    void initFog(osg::ref_ptr<osg::Group>, osg::ref_ptr<osgViewer::Viewer>);
    void initPlayer(osg::ref_ptr<osgViewer::Viewer>);
    void initManipulator(osg::ref_ptr<osgViewer::Viewer>);
    void initMap();

    typedef Factory<TexturingGroup> TexturingGroups;

    std::string _mapsPath;
    std::string _texturesPath;
    osg::ref_ptr<TexturingGroups> _texturingGroups;
    std::list< osg::ref_ptr<Chunk> > _chunks;
    osg::ref_ptr<ShapeFactory> _shapes;
    osg::ref_ptr<osg::Node> _player;
};

#endif
