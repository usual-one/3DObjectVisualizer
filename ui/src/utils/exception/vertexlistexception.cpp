#include "ui/include/utils/exceptions/vertexlistexception.h"

VertexListException::VertexListException() {
    msg_ = "VertexListException";
}

VertexListException::VertexListException(const std::string &msg) {
    msg_ = msg;
}

const char *VertexListException::what() const noexcept {
    return msg_.data();
}
