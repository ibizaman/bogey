#include <exception/TooCloseToOtherVectorException.h>

template<typename T>
DirectionMap<T>::DirectionMap()
    : osg::Referenced(),
      _cachedMinDistance(1),
      _inferiorLimit(1e-1)
{
}

template<typename T>
DirectionMap<T>::DirectionMap(double inferiorLimit)
    : osg::Referenced(),
      _cachedMinDistance(1),
      _inferiorLimit(inferiorLimit)
{
}

template<typename T>
DirectionMap<T>::DirectionMap(const DirectionMap& other)
    : osg::Referenced(other),
      _list(other.begin(), other.end()),
      _cachedMinDistance(other._cachedMinDistance),
      _inferiorLimit(other._inferiorLimit)
{
}

template<typename T>
void DirectionMap<T>::insert(const Pair& pair)
{
    set(pair.first, pair.second);
}

template<typename T>
void DirectionMap<T>::set(Direction direction, Element value)
{
    const Direction originalDirection = direction;
    direction.normalize();

    iterator closest = find(direction);
    if (closest != _list.end()) {
        const double distance = (direction - closest->first).length();
        if (distance < _inferiorLimit) {
            throw TooCloseToOtherVectorException(originalDirection, closest->first, _inferiorLimit);
        } else if (distance/2 < _cachedMinDistance) {
            _cachedMinDistance = distance/2;
        }
    }

    _list.push_back(Pair(direction, value));
}

template<typename T>
typename DirectionMap<T>::iterator DirectionMap<T>::find(Direction direction)
{
    direction.normalize();

    double minDistance = 2;
    iterator selectedDirection(_list.end());

    for (iterator directionIterator = _list.begin(); directionIterator != _list.end(); ++directionIterator) {

        double distance = (direction - directionIterator->first).length();

        if (distance <= _cachedMinDistance) {
            selectedDirection = directionIterator;
            break;
        } else if (distance <= minDistance) {
            minDistance = distance;
            selectedDirection = directionIterator;
        }
    }

    return selectedDirection;
}

template<typename T>
typename DirectionMap<T>::Element DirectionMap<T>::get(const Direction& direction)
{
    return find(direction)->second;
}

template<typename T>
int DirectionMap<T>::count(const Direction& direction)
{
    return find(direction) != _list.end();
}

template<typename T>
typename DirectionMap<T>::iterator DirectionMap<T>::begin()
{
    return _list.begin();
}

template<typename T>
typename DirectionMap<T>::iterator DirectionMap<T>::end()
{
    return _list.end();
}

template<typename T>
typename DirectionMap<T>::const_iterator DirectionMap<T>::begin() const
{
    return _list.begin();
}

template<typename T>
typename DirectionMap<T>::const_iterator DirectionMap<T>::end() const
{
    return _list.end();
}
