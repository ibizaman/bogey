#ifndef DIRECTIONMAP_HXX
#define DIRECTIONMAP_HXX

#include <osg/observer_ptr>
#include <list>
#include <osg/vec3d>

template<typename T>
class DirectionMap
{
public:
    typedef osg::Vec3d Direction;
    typedef osg::ref_ptr<T> Element;
    typedef std::pair<Direction, Element> Pair;
    typedef std::list<Pair> PairList;
    typedef typename PairList::iterator iterator;

    DirectionMap();
    DirectionMap(double);
    DirectionMap(const DirectionMap&);
    iterator find(Direction);
    Element get(const Direction&);
    void set(Direction, Element);
    void insert(const Pair&);
    int count(const Direction&);
    iterator begin();
    iterator end();

private:
    PairList _list;
    double _cachedMinDistance;
    double _inferiorLimit;
};

#include "DirectionMap.hpp"

#endif
