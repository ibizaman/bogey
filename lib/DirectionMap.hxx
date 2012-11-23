#ifndef DIRECTIONMAP_HXX
#define DIRECTIONMAP_HXX

#include <osg/Referenced>
#include <osg/observer_ptr>
#include <list>
#include <osg/vec3d>

template<typename T>
class DirectionMap : public osg::Referenced
{
public:
    typedef osg::Vec3d Direction;
    typedef osg::ref_ptr<T> Element;
    typedef std::pair<Direction, Element> Pair;
    typedef std::list<Pair> PairList;
    typedef typename PairList::iterator iterator;
    typedef typename PairList::const_iterator const_iterator;

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
    const_iterator begin() const;
    const_iterator end() const;

private:
    PairList _list;
    double _cachedMinDistance;
    double _inferiorLimit;
};

#include "DirectionMap.hpp"

#endif
