#ifndef MATRIXCALCULATOREXCEPTION_H
#define MATRIXCALCULATOREXCEPTION_H

#include <exception>
#include <string>

class MatrixCalculatorException : public std::exception {
public:
    MatrixCalculatorException();

    explicit MatrixCalculatorException(const std::string &msg);

    const char *what() const noexcept override;

protected:
    std::string msg_;

};

#endif // MATRIXCALCULATOREXCEPTION_H
