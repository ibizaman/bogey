#ifndef TOOCLOSETOOTHERVECTOREXCEPTION_H
#define	TOOCLOSETOOTHERVECTOREXCEPTION_H

#include <exception>
#include <osg/Vec3d>
#include <sstream>
#include <string>
using namespace std;

class TooCloseToOtherVectorException: public exception
{
private:
    osg::Vec3d _v1;
    osg::Vec3d _v2;
    double _limit;

public:
    TooCloseToOtherVectorException(const osg::Vec3d& v1, const osg::Vec3d& v2, double limit)
        : _v1(v1), _v2(v2), _limit(limit)
    {
    }

    ~TooCloseToOtherVectorException() throw() {}

    virtual const char* what() const throw()
    {
        stringstream stream;
        stream << "The vector " << _v1.x() << "," << _v1.y() << "," << _v1.z()
        << " is too close from " << _v2.x() << "," << _v2.y() << "," << _v2.z()
        << " : the limit is " << _limit;
        return stream.str().c_str();
    }
};

#endif
