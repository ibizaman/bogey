#ifndef CUBE_H
#define CUBE_H

#include "lib/TexturingGeode.h"
#include <map>
#include "object/Face.h"

class Cube : public TexturingGeode
{
public:
    Cube();

private:
    typedef std::map< Face::Direction, osg::ref_ptr<Face> > Faces;
    Faces _faces;
};

#endif
