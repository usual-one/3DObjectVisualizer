#include "logic/include/obj3d/figure/components/figuremeta.h"

FigureMeta::FigureMeta() :
    saved_(true),
    path_(std::make_shared<std::string>()) {}

std::shared_ptr<std::string> FigureMeta::getPath() {
    return path_;
}

bool FigureMeta::isSaved() {
    return saved_;
}

void FigureMeta::setPath(const std::string &path) {
    *path_ = path;
}

void FigureMeta::setSaved(bool saved) {
    saved_ = saved;
}
