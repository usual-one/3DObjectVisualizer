#include "logic/include/utils/exception/stringsplitterexception.h"

StringSplitterException::StringSplitterException() {
    msg_ = "StringSplitterException";
}

StringSplitterException::StringSplitterException(const std::string &msg) {
    msg_ = msg;
}

const char *StringSplitterException::what() const noexcept {
    return msg_.data();
}
