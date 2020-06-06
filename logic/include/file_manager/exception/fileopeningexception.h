#ifndef FILEOPENINGEXCEPTION_H
#define FILEOPENINGEXCEPTION_H

#include "logic/include/file_manager/exception/fileexception.h"

class FileOpeningException : public FileException {
public:
    FileOpeningException() :
        FileException() {}

    FileOpeningException(const std::string &msg) :
        FileException(msg) {}

    FileOpeningException(const std::string &msg, const std::string &path) :
        FileException(msg),
        path_(path) {}

private:
    std::string path_;

};

#endif // FILEOPENINGEXCEPTION_H
