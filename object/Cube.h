#ifndef CUBE_H
#define CUBE_H

#include "lib/GeometryGeode.h"

class Cube : public GeometryGeode
{
public:
    Cube();
    void init();

protected:
    void createVertices(Vertices&);
    void createElements(ElementsList&);
    void createTexture(Texture&);

private:
    int _attribLocation;
};

#endif
