#ifndef ELEMENTDONOTEXIST_H
#define ELEMENTDONOTEXIST_H

#include "BaseException.h"

class ElementDoNotExist : public BaseException
{
public:
    ElementDoNotExist(std::string elem) : BaseException(elem) {}
    const char* message() const {return "The element do not exist";}
};

#endif
