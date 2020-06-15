#include "logic/include/scene/scenemanager.h"

SceneManager::SceneManager() :
    constructor_(std::make_unique<SceneConstructor>()),
    drawer_(nullptr),
    scene_(std::make_shared<Scene>()) {}

SceneManager::SceneManager(std::unique_ptr<BaseSceneDrawer> drawer) :
    constructor_(std::make_unique<SceneConstructor>()),
    drawer_(std::move(drawer)),
    scene_(std::make_shared<Scene>()) {}

bool SceneManager::hasDrawer() {
    return drawer_ != nullptr;
}

void SceneManager::redrawScene() {
    std::vector<std::shared_ptr<CanvasFigure>> canvas_figures = createCanvasFigures();
    std::shared_ptr<obj3d::Rectangle2D> camera_scope = constructor_->getScope();

    for (auto figure : canvas_figures) {
        figure->changeOrigin(*camera_scope->getLeftBottom());
    }

    drawer_->drawFigures(canvas_figures, camera_scope);
}

std::shared_ptr<Scene> SceneManager::getScene() {
    return scene_;
}

void SceneManager::setDrawer(std::unique_ptr<BaseSceneDrawer> drawer) {
    drawer_ = std::move(drawer);
}

void SceneManager::drawScene() {
    std::vector<std::shared_ptr<CanvasFigure>> canvas_figures = createCanvasFigures();

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
    scene_->update(other);
}

std::vector<std::shared_ptr<CanvasFigure>> SceneManager::createCanvasFigures() {
    std::vector<std::shared_ptr<obj3d::Figure>> figures = {};
    for (auto tag : scene_->getFiguresTags()) {
        std::shared_ptr<obj3d::Figure> figure = scene_->getFigure(*tag);
        if (!figure->getSessionState()->isHidden()) {
            figures.push_back(figure);
        }
    }

    return constructor_->convertToCanvasFigures(figures);
}
