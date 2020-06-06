#ifndef FIGUREFILEMANAGER_H
#define FIGUREFILEMANAGER_H

#include <memory>

#include "logic/include/obj3d/figure/figure3d.h"

class FigureFileManager{
public:
    std::shared_ptr<obj3d::Figure> read(const std::string &path);

    void save(const std::shared_ptr<obj3d::Figure> &figure);

    void save_as(const std::string &path, const std::shared_ptr<obj3d::Figure> &figure);

};

#endif // FIGUREFILEMANAGER_H
