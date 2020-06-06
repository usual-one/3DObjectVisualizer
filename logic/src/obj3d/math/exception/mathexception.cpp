#include "logic/include/obj3d/math/exception/mathexception.h"

MathException::MathException() {
    msg_ = "MathException";
}

MathException::MathException(const std::string &msg) {
    msg_ = msg;
}

const char *MathException::what() const noexcept {
    return msg_.data();
}
