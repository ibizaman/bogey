#include "Cube.h"
#include "transform/FaceTransform.h"

Cube::Cube(double size, osg::ref_ptr<ShapeFactory> factory)
{
    std::list<osg::Vec3d> cubeDirections;
    cubeDirections.push_back(osg::Vec3d( 1, 0, 0));
    cubeDirections.push_back(osg::Vec3d( 0, 1, 0));
    cubeDirections.push_back(osg::Vec3d(-1, 0, 0));
    cubeDirections.push_back(osg::Vec3d( 0,-1, 0));
    cubeDirections.push_back(osg::Vec3d( 0, 0, 1));
    cubeDirections.push_back(osg::Vec3d( 0, 0,-1));

    osg::ref_ptr<ShapeTransform::Faces> directionMap(new ShapeTransform::Faces());

    const double ratio = 1.0/6.0;
    int textureNum = 0;
    for (std::list<osg::Vec3d>::iterator direction = cubeDirections.begin(); direction != cubeDirections.end(); ++direction) {

        osg::ref_ptr<TexturedDrawable> drawable(factory->getSquare(osg::Vec2d(textureNum*ratio, 0), osg::Vec2d(ratio, 1), size));

        osg::ref_ptr<FaceTransform> face(new FaceTransform(drawable));
        factory->translate(face.get(), *direction, size/2);

        directionMap->set(*direction, face);

        ++textureNum;
    }

    setBoundingBox(osg::BoundingBox(-.5, .5, -.5, .5, -.5, .5));

    ShapeTransform::init(directionMap);
}
