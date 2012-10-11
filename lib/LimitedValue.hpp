template<typename T>
LimitedValue<T>::LimitedValue(const T& value)
    : _value(value),
      _min(-1),
      _max(1)
{
}

template<typename T>
LimitedValue<T>::LimitedValue(const T& value, const T& min, const T& max)
    : _value(value),
      _min(min),
      _max(max)
{
}

template<typename T>
void LimitedValue<T>::operator=(const T& value)
{
    _value = value;
}

template<typename T>
bool LimitedValue<T>::operator==(const T& value)
{
    return _value == value;
}

template<typename T>
void LimitedValue<T>::operator+=(const T& value)
{
    _value += value;
    if (_value > _max) {
        _value = _max;
    }
}

template<typename T>
void LimitedValue<T>::operator-=(const T& value)
{
    _value -= value;
    if (_value < _min) {
        _value = _min;
    }
}

template<typename T>
bool LimitedValue<T>::operator>(const T& value)
{
    return _value > value;
}

template<typename T>
bool LimitedValue<T>::operator>=(const T& value)
{
    return _value >= value;
}

template<typename T>
bool LimitedValue<T>::operator<(const T& value)
{
    return _value < value;
}

template<typename T>
bool LimitedValue<T>::operator<=(const T& value)
{
    return _value <= value;
}

template<typename V>
std::ostream& operator<<(std::ostream& out, const LimitedValue<V>& value)
{
    out << value._value << " [" << value._min << ", " << value._max << "]";
    return out;
}

template<typename T>
void LimitedValue<T>::setMin(const T& min)
{
    _min = min;
}

template<typename T>
const T& LimitedValue<T>::getMin() const
{
    return _min;
}

template<typename T>
void LimitedValue<T>::setMax(const T& max)
{
    _max = max;
}

template<typename T>
const T& LimitedValue<T>::getMax() const
{
    return _max;
}

template<typename T>
const T& LimitedValue<T>::value() const
{
    return _value;
}
