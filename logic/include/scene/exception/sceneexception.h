#ifndef SCENEEXCEPTION_H
#define SCENEEXCEPTION_H

#include <exception>
#include <string>

class SceneException : public std::exception {
public:
    SceneException();

    explicit SceneException(const std::string &msg);

    const char *what() const noexcept override;

protected:
    std::string msg_;

};

#endif // SCENEEXCEPTION_H
