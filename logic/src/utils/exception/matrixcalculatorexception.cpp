#include "logic/include/utils/exception/matrixcalculatorexception.h"

MatrixCalculatorException::MatrixCalculatorException() {
    msg_ = "MatrixCalculatorException";
}

MatrixCalculatorException::MatrixCalculatorException(const std::string &msg) {
    msg_ = msg;
}

const char *MatrixCalculatorException::what() const noexcept {
    return msg_.data();
}
