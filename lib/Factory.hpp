#include "exception/ElementDoNotExist.h"
#include "exception/ElementAlreadyExists.h"

template<typename T, typename K>
Factory<T,K>::Factory(bool notErasable)
    : _notErasable(notErasable)
{
}

template<typename T, typename K>
void Factory<T,K>::insert(K key, Element element)
{
    if (_notErasable && isElement(key)) {
        throw ElementAlreadyExists(key);
    }
    _map[key] = element;
}

template<typename T, typename K>
bool Factory<T,K>::isElement(K key)
{
    return _map.count(key) == 1;
}

template<typename T, typename K>
typename Factory<T,K>::Element Factory<T,K>::getOriginal(K key)
{
    typename Factory<T,K>::iterator it = _map.find(key);
    if (it == end()) {
        throw ElementDoNotExist(key);
    }
    return it->second.get();
}

template<typename T, typename K>
typename Factory<T,K>::Element Factory<T,K>::getCopy(K key) const
{
    typename Factory<T,K>::const_iterator it = _map.find(key);
    if (it == end()) {
        throw ElementDoNotExist(key);
    }
    return new T(*it->second.get());
}

template<typename T, typename K>
typename Factory<T,K>::const_iterator Factory<T,K>::begin() const
{
    return _map.begin();
}

template<typename T, typename K>
typename Factory<T,K>::const_iterator Factory<T,K>::end() const
{
    return _map.end();
}
