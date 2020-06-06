#include "logic/include/scene/scenemanager.h"

SceneManager::SceneManager() :
    constructor_(std::make_unique<SceneConstructor>()),
    drawer_(nullptr),
    scene_(nullptr) {}

SceneManager::SceneManager(std::unique_ptr<BaseSceneDrawer> drawer) :
    constructor_(std::make_unique<SceneConstructor>()),
    drawer_(std::move(drawer)),
    scene_(nullptr) {}

bool SceneManager::hasScene() {
    return scene_ != nullptr;
}

bool SceneManager::hasDrawer() {
    return drawer_ != nullptr;
}

void SceneManager::setScene(const Scene &scene) {
    scene_ = std::make_shared<Scene>(scene);
}

std::shared_ptr<Scene> SceneManager::getScene() {
    return scene_;
}

void SceneManager::setDrawer(std::unique_ptr<BaseSceneDrawer> drawer) {
    drawer_ = std::move(drawer);
}

void SceneManager::drawScene() {
    std::vector<std::shared_ptr<obj3d::Figure>> figures = {};
    for (auto tag : scene_->getFiguresTags()) {
        figures.push_back(scene_->getFigure(*tag));
    }

    std::vector<std::shared_ptr<CanvasFigure>> canvas_figures =
            constructor_->convertToCanvasFigures(figures);

    std::vector<obj3d::Point2D> figures_pts = {};
    for (auto figure : canvas_figures) {
        std::vector<obj3d::Point2D> figure_pts = figure->toPoints();
        figures_pts.insert(figures_pts.end(), figure_pts.begin(), figure_pts.end());
    }
    std::shared_ptr<obj3d::Rectangle2D> camera_scope = constructor_->getScope(figures_pts);

    for (auto figure : canvas_figures) {
        figure->changeOrigin(*camera_scope->getLeftBottom());
    }

    drawer_->drawFigures(canvas_figures, camera_scope);
}

void SceneManager::updateScene(const Scene &other) {
    if (hasScene()) {
        scene_->update(other);
    } else {
        setScene(other);
    }
}
