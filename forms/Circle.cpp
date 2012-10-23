#include "forms/Circle.h"
#include <cmath>

Circle::Circle(std::string type , double diameter , osg::Vec3d GPos)
    : osg::PositionAttitudeTransform() , _type(type) , _diameter(diameter) , _GPos(GPos)
{
    create();    
}

void Circle::create() {
    const double radius = _diameter/2;
    double XPos = _GPos.x() - 2*radius + 1;
    double YPos = _GPos.y() + 2*radius - 1;
    double ZPos = _GPos.z() + 1;
    setPosition(_GPos);
    double CurrentRadius;
    
    for(int i = 1 ; i <= _diameter ; i++) {
        for(int j = 1 ; j <= _diameter ; j++) {
            CurrentRadius = (sqrt(pow(XPos - _GPos.x() , 2) + pow(YPos - _GPos.y() , 2)));
            if(CurrentRadius <= 2*radius) {
                osg::ref_ptr<Cube> cube(new Cube(_type));
                osg::ref_ptr<osg::PositionAttitudeTransform> cubeTransform(new osg::PositionAttitudeTransform());
                cubeTransform->addChild(cube);
                cubeTransform->setPosition(osg::Vec3d(XPos,YPos,ZPos));
                addChild(cubeTransform);   
            }
            
            XPos += 2.0;
            
        }
        YPos -= 2.0;
        XPos -=2.0*_diameter;
    }
}