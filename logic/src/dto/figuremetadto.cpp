#include "logic/include/dto/figuremetadto.h"

FigureMetaDTO::FigureMetaDTO(const std::string &path) :
    path_(path) {}

std::string &FigureMetaDTO::getPath() {
    return path_;
}

void FigureMetaDTO::setPath(const std::string &path) {
    path_ = path;
}
