#include "Chunk.h"

Chunk::Chunk(std::string type , osg::Vec3d GPos , Perlin3D perlin)
    : osg::PositionAttitudeTransform() , _type(type) , _GPos(GPos)
{
    for (int i = 0 ; i < 16 ; i++) {
        for (int j = 0 ; j < 16 ; j++) {
            for (int k = 0 ; k < 16 ; k++) {
                _chunk[i][j][k] = perlin.getChunk(i,j,k);
            }
        }
    }
    create();    
}

void Chunk::create() {
    double XPos = _GPos.x() - 16;
    double YPos = _GPos.y() + 16;
    double ZPos = _GPos.z() - 16;
    
    setPosition(_GPos);
        
    for(int k = 1 ; k<= 16 ; k++) {
        for(int i = 1 ; i <= 16 ; i++) {
            for(int j = 1 ; j <= 16 ; j++) {
                if(_chunk[k][i][j] > 0.5) {
                    osg::ref_ptr<Cube> cube(new Cube(_type));
                    osg::ref_ptr<osg::PositionAttitudeTransform> cubeTransform(new osg::PositionAttitudeTransform());
                    cubeTransform->addChild(cube);
                    cubeTransform->setPosition(osg::Vec3d(XPos,YPos,ZPos));
                    addChild(cubeTransform);
                }

                XPos += 2.0;

            }
            YPos -= 2.0;
            XPos -=2.0*16;
        }
        YPos +=2.0*16;
        ZPos += 2.0;
    }
}