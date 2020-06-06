#ifndef FILEWRITINGEXCEPTION_H
#define FILEWRITINGEXCEPTION_H

#include "logic/include/file_manager/exception/fileexception.h"

class FileWritingException : public FileException {
public:
    FileWritingException() :
        FileException() {}

    FileWritingException(const std::string &msg) :
        FileException(msg) {}

    FileWritingException(const std::string &msg, const std::string &path) :
        FileException(msg),
        path_(path) {}

private:
    std::string path_;

};

#endif // FILEWRITINGEXCEPTION_H
