#include "logic/include/scene/exception/sceneexception.h"

SceneException::SceneException() {
    msg_ = "SceneException";
}

SceneException::SceneException(const std::string &msg) {
    msg_ = msg;
}

const char *SceneException::what() const noexcept {
    return msg_.data();
}
