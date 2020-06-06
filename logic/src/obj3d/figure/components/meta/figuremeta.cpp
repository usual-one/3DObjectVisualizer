#include "logic/include/obj3d/figure/components/meta/figuremeta.h"

FigureMeta::FigureMeta() :
    path_(std::make_shared<std::string>()),
    location_(std::make_shared<Location>()) {}

std::shared_ptr<std::string> FigureMeta::getPath() {
    return path_;
}

std::shared_ptr<Location> FigureMeta::getLocation() {
    return location_;
}
