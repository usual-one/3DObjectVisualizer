#ifndef MATRIXEXCEPTION_H
#define MATRIXEXCEPTION_H

#include "logic/include/obj3d/math/exception/mathexception.h"


class MatrixException : public MathException {
public:
    MatrixException() :
        MathException() {}

    MatrixException(const std::string &msg) :
        MathException(msg) {}

};


#endif // MATRIXEXCEPTION_H
