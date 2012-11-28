#ifndef ERROROPENINGFILEEXCEPTION_H
#define ERROROPENINGFILEEXCEPTION_H

#include "BaseException.h"

class ErrorOpeningFileException : public BaseException
{
public:
    ErrorOpeningFileException(std::string elem) : BaseException(elem) {}
    const char* message() const {return "The file cannot be opened";}
};

#endif
