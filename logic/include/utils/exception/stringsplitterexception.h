#ifndef STRINGSPLITTEREXCEPTION_H
#define STRINGSPLITTEREXCEPTION_H

#include <exception>
#include <string>

class StringSplitterException : public std::exception {
public:
    StringSplitterException();

    explicit StringSplitterException(const std::string &msg);

    const char *what() const noexcept override;

protected:
    std::string msg_;

};

#endif // STRINGSPLITTEREXCEPTION_H
