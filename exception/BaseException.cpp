#include "BaseException.h"
#include <sstream>

BaseException::BaseException(std::string elem)
    : _elem(elem)
{
}

BaseException::~BaseException() throw()
{
}

const char* BaseException::what() const throw()
{
    std::stringstream stream;
    stream << "ERROR " << message();
    if (!_elem.empty()) {
        stream << " (" << _elem << ")";
    }
    return stream.str().c_str();
}
