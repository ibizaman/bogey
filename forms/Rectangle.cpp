#include "forms/Rectangle.h"

Rectangle::Rectangle(std::string type , double length , double width , osg::Vec3d GPos)
    : osg::PositionAttitudeTransform() , _type(type) , _length(length) , _width(width) , _GPos(GPos)
{
    create();    
}

void Rectangle::create() {
    double XPos = _GPos.x() - _length;
    double YPos = _GPos.y() + _width;
    double ZPos = _GPos.z();
    
    setPosition(_GPos);
        
    for(int i = 1 ; i <= _width ; i++) {
        for(int j = 1 ; j <= _length ; j++) {
            osg::ref_ptr<Cube> cube(new Cube(_type));
            osg::ref_ptr<osg::PositionAttitudeTransform> cubeTransform(new osg::PositionAttitudeTransform());
            cubeTransform->addChild(cube);
            cubeTransform->setPosition(osg::Vec3d(XPos,YPos,ZPos));
            addChild(cubeTransform);
            
            XPos += 2.0;
            
        }
        YPos -= 2.0;
        XPos -=2.0*_length;
    }
}

