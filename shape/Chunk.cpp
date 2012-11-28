#include "Chunk.h"
#include <osg/BoundingBox>

Chunk::Chunk(Shape element, const Perlin3D& perlin)
    : osg::PositionAttitudeTransform()
{
    const int chunkSize = perlin.getChunkSize();
    double XPos = - chunkSize/2;
    double YPos = chunkSize/2;
    double ZPos = - chunkSize/2;
    const osg::Vec3d elementSize(
            element->getBoundingBox().xMax() - element->getBoundingBox().xMin(),
            element->getBoundingBox().yMax() - element->getBoundingBox().yMin(),
            element->getBoundingBox().zMax() - element->getBoundingBox().zMin()
        );

    for (int k = 1 ; k <= chunkSize ; k++) {
        for (int i = 1 ; i <= chunkSize ; i++) {
            for (int j = 1 ; j <= chunkSize ; j++) {

                if (perlin.isChunkTrue(i,j,k)) {
                    Shape cube(new ShapeTransform(*element.get()));
                    cube->setPosition(osg::Vec3d(XPos,YPos,ZPos));
                    addChild(cube);
                }

                XPos += elementSize.x();
            }
            YPos -= elementSize.y();
            XPos -= elementSize.x()*chunkSize;
        }
        YPos += elementSize.y()*chunkSize;
        ZPos += elementSize.z();
    }
}
