#include "logic/include/scene/constructor/sceneconstructor.h"

SceneConstructor::SceneConstructor() :
    camera_(std::make_shared<Camera>()) {}

SceneConstructor::SceneConstructor(const obj3d::Plane &camera_plane) :
    camera_(std::make_shared<Camera>(camera_plane)) {}

bool SceneConstructor::hasCamera() {
    return camera_ != nullptr;
}

std::shared_ptr<obj3d::Rectangle2D> SceneConstructor::getScope() {
    return camera_->getScope();
}

std::shared_ptr<obj3d::Rectangle2D> SceneConstructor::getScope(
        const std::vector<obj3d::Point2D> &projected_points) {
    if (projected_points.empty()) {
        return camera_->getScope();
    }
    return camera_->calculateScope(projected_points);
}

std::vector<std::shared_ptr<CanvasFigure>> SceneConstructor::convertToCanvasFigures(
        const std::vector<std::shared_ptr<obj3d::Figure>> &figures) {
    std::vector<std::shared_ptr<CanvasFigure>> canvas_figures = {};
    for (auto figure : figures) {
        canvas_figures.push_back(std::make_shared<CanvasFigure>(*figure, *camera_));
    }
    return canvas_figures;
}
