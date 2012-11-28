#ifndef ELEMENTALREADYEXISTS_H
#define ELEMENTALREADYEXISTS_H

#include "BaseException.h"

class ElementAlreadyExists : public BaseException
{
public:
    ElementAlreadyExists(std::string elem) : BaseException(elem) {}
    const char* message() const {return "The element already exists";}
};

#endif
