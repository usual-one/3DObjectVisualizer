#include "logic/include/obj3d/figure/components/meta/figuremeta.h"

FigureMeta::FigureMeta() :
    hidden_(false),
    saved_(true),
    location_(std::make_shared<State>()),
    path_(std::make_shared<std::string>()) {}

std::shared_ptr<std::string> FigureMeta::getPath() {
    return path_;
}

bool FigureMeta::isHidden() {
    return hidden_;
}

bool FigureMeta::isSaved() {
    return saved_;
}

void FigureMeta::setHidden(bool hidden) {
    hidden_ = hidden;
}

void FigureMeta::setPath(const std::string &path) {
    *path_ = path;
}

void FigureMeta::setSaved(bool saved) {
    saved_ = saved;
}

std::shared_ptr<State> FigureMeta::getLocation() {
    return location_;
}
