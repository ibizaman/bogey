#ifndef FACTORY_HXX
#define FACTORY_HXX

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <map>
#include <string>

template<typename T, typename K = std::string>
class Factory : public osg::Referenced
{
public:
    typedef osg::ref_ptr<T> Element;
    typedef typename std::map<K,Element>::iterator iterator;
    typedef typename std::map<K,Element>::const_iterator const_iterator;

    Factory(bool);
    void insert(K, Element);
    bool isElement(K);
    Element getOriginal(K);
    Element getCopy(K) const;
    const_iterator begin() const;
    const_iterator end() const;

private:
    const bool _notErasable;
    std::map<K,Element> _map;
};

#include "Factory.hpp"

#endif
