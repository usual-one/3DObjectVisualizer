#ifndef BASISEXCEPTION_H
#define BASISEXCEPTION_H

#include "logic/include/obj3d/math/exception/mathexception.h"


class BasisException : public MathException {
public:
    BasisException() :
        MathException() {}

    BasisException(const std::string &msg) :
        MathException(msg) {}

};


#endif // BASISEXCEPTION_H
