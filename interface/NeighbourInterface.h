#ifndef NEIGHBOURINTERFACE_H
#define NEIGHBOURINTERFACE_H

#include <osg/observer_ptr>

class NeighbourInterface
{
public:
    typedef osg::observer_ptr<NeighbourInterface> Neighbour;

    virtual void bindNeighbour(NeighbourInterface*) = 0;
    virtual void unbindNeighbour() = 0;
};

#endif
