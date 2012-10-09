#ifndef TRISTATE_H
#define TRISTATE_H

#include <osg/Referenced>

class TriState : public osg::Referenced
{
public:
    enum State {ZERO, PLUS, MINUS};

    TriState();

    void operator=(const TriState&);
    TriState& operator++();
    TriState& operator--();
    bool oppositeOf(const TriState&);
    bool operator==(const TriState&);
    bool operator==(State);
    bool operator!=(const TriState&);

    int asInt() const;
    void reset();
    State state() const;

protected:

    State _state;
};

#endif
