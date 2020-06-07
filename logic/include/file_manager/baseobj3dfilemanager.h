#ifndef BASEFILEMANAGER_H
#define BASEFILEMANAGER_H

#include <string>

#include "logic/include/scene/scene.h"

class BaseObj3DFileManager {
public:
    virtual Scene read(const std::string &path) = 0;

    virtual void saveFigure(std::shared_ptr<obj3d::Figure> figure) = 0;

//    virtual void save(const Scene &scene) = 0;

//    virtual void save_as(const std::string &path, const Scene &scene) = 0;

protected:
    std::string path_;
};

#endif // BASEFILEMANAGER_H
