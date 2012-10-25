#ifndef DUMMYOSGREFERENCEDCLASS_H
#define DUMMYOSGREFERENCEDCLASS_H

#include <osg/Referenced>

class DummyOsgReferencedClass : public osg::Referenced
{
public:
    DummyOsgReferencedClass(int i) : _i(i) {}

    void setI(int i) {
        _i = i;
    }

    int getI() const {
        return _i;
    }

private:
    int _i;
};

#endif
