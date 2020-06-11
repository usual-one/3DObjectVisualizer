#ifndef FIGUREMETA_H
#define FIGUREMETA_H

#include <memory>
#include <string>

#include "logic/include/obj3d/figure/components/meta/location.h"


class FigureMeta {
public:
    FigureMeta();

    std::shared_ptr<Location> getLocation();

    std::shared_ptr<std::string> getPath();

    bool isHidden();

    bool isSaved();

    void setHidden(bool hidden);

    void setPath(const std::string &path);

    void setSaved(bool saved);

private:
    bool hidden_;

    bool saved_;

    std::shared_ptr<Location> location_;

    std::shared_ptr<std::string> path_;

};

#endif // FIGUREMETA_H
