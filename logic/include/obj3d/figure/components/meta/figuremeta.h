#ifndef FIGUREMETA_H
#define FIGUREMETA_H

#include <memory>
#include <string>

#include "logic/include/obj3d/figure/components/meta/location.h"


class FigureMeta {
public:
    FigureMeta();

    std::shared_ptr<std::string> getPath();

    std::shared_ptr<Location> getLocation();

private:
    std::shared_ptr<std::string> path_;

    std::shared_ptr<Location> location_;
};

#endif // FIGUREMETA_H
