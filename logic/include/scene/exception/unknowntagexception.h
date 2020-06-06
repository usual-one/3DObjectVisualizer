#ifndef UNKNOWNTAGEXCEPTION_H
#define UNKNOWNTAGEXCEPTION_H

#include "logic/include/scene/exception/sceneexception.h"

class UnknownTagException : public SceneException {
public:
    UnknownTagException() :
        SceneException() {}

    UnknownTagException(const std::string &msg) :
        SceneException(msg) {}

    UnknownTagException(const std::string &msg, const std::string &tag) :
        SceneException(msg),
        tag_(tag) {}

private:
    std::string tag_;

};

#endif // UNKNOWNTAGEXCEPTION_H
