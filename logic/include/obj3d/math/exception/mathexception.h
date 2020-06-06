#ifndef MATHEXCEPTION_H
#define MATHEXCEPTION_H

#include <exception>
#include <string>

class MathException : public std::exception {
public:
    MathException();

    explicit MathException(const std::string &msg);

    const char *what() const noexcept override;

protected:
    std::string msg_;

};

#endif // MATHEXCEPTION_H
