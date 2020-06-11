#ifndef VERTEXLISTEXCEPTION_H
#define VERTEXLISTEXCEPTION_H

#include <exception>
#include <string>

class VertexListException : public std::exception {
public:
    VertexListException();

    explicit VertexListException(const std::string &msg);

    const char *what() const noexcept override;

protected:
    std::string msg_;

};

#endif // VERTEXLISTEXCEPTION_H
