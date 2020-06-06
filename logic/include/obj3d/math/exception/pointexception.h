#ifndef POINTEXCEPTION_H
#define POINTEXCEPTION_H

#include "logic/include/obj3d/math/exception/mathexception.h"


class PointException : public MathException {
public:
    PointException() :
        MathException() {}

    PointException(const std::string &msg) :
        MathException(msg) {}

};

#endif // POINTEXCEPTION_H
