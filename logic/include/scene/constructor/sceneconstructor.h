#ifndef SCENECONSTRUCTOR_H
#define SCENECONSTRUCTOR_H

#include <memory>

#include "logic/include/scene/scene.h"
#include "logic/include/scene/constructor/camera.h"
#include "logic/include/scene/constructor/figure/canvasfigure.h"


class SceneConstructor {
public:
    SceneConstructor();

    SceneConstructor(const obj3d::Plane &camera_plane);

    std::vector<std::shared_ptr<CanvasFigure>> convertToCanvasFigures(
            const std::vector<std::shared_ptr<obj3d::Figure>> &figures);

    std::shared_ptr<obj3d::Rectangle2D> getScope();

    std::shared_ptr<obj3d::Rectangle2D> getScope(const std::vector<obj3d::Point2D> &projected_points);

    bool hasCamera();

private:
    std::shared_ptr<Camera> camera_;

};

#endif // SCENECONSTRUCTOR_H
