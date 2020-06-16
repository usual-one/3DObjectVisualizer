#include "logic/include/file_manager/exception/fileexception.h"

FileException::FileException() {
    msg_ = "FileException";
}

FileException::FileException(const std::string &msg) {
    msg_ = msg;
}

const char *FileException::what() const noexcept {
    return msg_.data();
}
