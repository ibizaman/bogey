#ifndef FACE_H
#define FACE_H

#include "lib/TexturedDrawable.h"

class Face : public TexturedDrawable
{
public:
    enum Direction {TOP, BOTTOM, FRONT, BACK, LEFT, RIGHT};

    Face(Direction);

protected:
    void createVertices(Vertices&);
    void createElements(ElementsList&);
    void createTextureCoords(TextureCoords&);

private:
    Direction _direction;
};

#endif
