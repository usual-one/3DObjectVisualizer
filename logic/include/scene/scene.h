#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

#include "logic/include/obj3d/figure/figure.h"
#include "logic/include/obj3d/surface/surface.h"

class Scene {
public:
    Scene();

    void appendSurface(std::shared_ptr<obj3d::Surface> surface);

    void appendFigure(std::shared_ptr<obj3d::Figure> figure);

    void appendFigure(obj3d::Figure figure);

    bool containsSurface(const std::string &tag);

    bool containsFigure(const std::string &tag);

    void deleteFigure(const std::string &tag);

    void deleteSurface(const std::string &tag);

    bool isFigureTag(const std::string &tag);

    std::vector<std::shared_ptr<std::string>> getSurfacesTags();

    std::vector<std::shared_ptr<std::string>> getFiguresTags();

    std::shared_ptr<obj3d::Surface> getSurface(const std::string &tag);

    std::shared_ptr<obj3d::Figure> getFigure(const std::string &tag);

    void transformFigure(const std::string &tag, const obj3d::Matrix &transform_matr);

    void update(const Scene &other);

private:
    std::vector<std::shared_ptr<obj3d::Figure>> figures_;

    std::vector<std::shared_ptr<obj3d::Surface>> surfaces_;

};

#endif // SCENE_H
