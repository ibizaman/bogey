#ifndef TOGGLEINTERFACE_H
#define TOGGLEINTERFACE_H

class ToggleInterface
{
public:
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual void toggle() = 0;
};

#endif
