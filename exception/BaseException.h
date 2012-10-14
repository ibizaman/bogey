#ifndef BASEEXCEPTION_H
#define BASEEXCEPTION_H

#include <exception>
#include <string>

class BaseException: public std::exception
{
private:
    std::string _elem;

public:
    BaseException(std::string = "");
    ~BaseException() throw();

    virtual const char* what() const throw();
    virtual const char* message() const = 0;
    virtual int errornum() const = 0;
};

#endif
