#include "TriState.h"

TriState::TriState()
    : _state(ZERO)
{
}

void TriState::operator=(const TriState& other)
{
    _state = other._state;
}

TriState& TriState::operator++()
{
    if (_state == ZERO) {
        _state = PLUS;
    } else if (_state == MINUS) {
        _state = ZERO;
    }
    return *this;
}

TriState& TriState::operator--()
{
    if (_state == ZERO) {
        _state = MINUS;
    } else if (_state == PLUS) {
        _state = ZERO;
    }
    return *this;
}

bool TriState::oppositeOf(const TriState& other)
{
    return (_state == PLUS && other._state == MINUS)
        || (_state == MINUS && other._state == PLUS);
}

bool TriState::operator==(const TriState& other)
{
    return _state == other._state;
}

bool TriState::operator==(State state)
{
    return _state == state;
}

bool TriState::operator!=(const TriState& other)
{
    return !(_state == other._state);
}

int TriState::asInt() const
{
    int value;
    switch (_state) {
        case PLUS:
            value = 1;
        case ZERO:
            value = 0;
        case MINUS:
            value = -1;
    }
    return value;
}

void TriState::reset()
{
    _state = ZERO;
}

TriState::State TriState::state() const
{
    return _state;
}
