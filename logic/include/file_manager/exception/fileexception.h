#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H

#include <exception>
#include <string>

class FileException : public std::exception {
public:
    FileException();

    explicit FileException(const std::string &msg);

    const char *what() const noexcept override;

protected:
    std::string msg_;

};

#endif // FILEEXCEPTION_H
