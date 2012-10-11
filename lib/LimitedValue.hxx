#ifndef LIMITEDVALUE_H
#define LIMITEDVALUE_H

#include <iostream>

template<typename T>
class LimitedValue
{
public:
    LimitedValue(const T&);
    LimitedValue(const T&, const T&, const T&);
    void operator=(const T&);
    bool operator==(const T&);
    void operator+=(const T&);
    void operator-=(const T&);
    bool operator>(const T&);
    bool operator>=(const T&);
    bool operator<(const T&);
    bool operator<=(const T&);
    template<typename V>
    friend std::ostream& operator<<(std::ostream&, const LimitedValue<V>&);
    void setMin(const T&);
    const T& getMin() const;
    void setMax(const T&);
    const T& getMax() const;
    const T& value() const;

private:
    T _value;
    T _min;
    T _max;
};

#include "LimitedValue.hpp"

#endif
