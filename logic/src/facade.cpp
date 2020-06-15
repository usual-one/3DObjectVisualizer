#include "logic/include/facade.h"
#include "logic/include/obj3d/math/transformmatrixbuilder.h"

Facade::Facade() :
    file_manager_(nullptr),
    scene_manager_(nullptr),
    has_changes_(false) {}

Facade::Facade(std::unique_ptr<BaseObj3DFileManager> file_manager,
               std::unique_ptr<SceneManager> scene_manager) :
    file_manager_(std::move(file_manager)),
    scene_manager_(std::move(scene_manager)),
    has_changes_(false) {}

std::shared_ptr<std::string> Facade::addNewFigure() {
    obj3d::Figure figure;
    scene_manager_->getScene()->appendFigure(figure);
    return figure.getTag();
}

void Facade::changeLocation(const std::string tag, std::shared_ptr<State> location) {
    std::shared_ptr<obj3d::Figure> figure = getFigure(tag);
    std::shared_ptr<State> current_location = figure->getState();

    if (*location->getMovement() != *current_location->getMovement()) {
        moveFigure(tag, location->getMovement()->getX() - current_location->getMovement()->getX(),
                   location->getMovement()->getY() - current_location->getMovement()->getY(),
                   location->getMovement()->getZ() - current_location->getMovement()->getZ());
    }
    if (*location->getRotation() != *current_location->getRotation()) {
        rotateFigure(tag, location->getRotation()->getX() - current_location->getRotation()->getX(),
                   location->getRotation()->getY() - current_location->getRotation()->getY(),
                   location->getRotation()->getZ() - current_location->getRotation()->getZ());
    }
    if (*location->getScaling() != *current_location->getScaling()) {
        scaleFigure(tag, location->getScaling()->getX() / current_location->getScaling()->getX(),
                    location->getScaling()->getY() / current_location->getScaling()->getY(),
                    location->getScaling()->getZ() / current_location->getScaling()->getZ());
    }
    figure->getState()->copy(*location);
}

void Facade::deleteSurface(const std::string &tag) {
    scene_manager_->getScene()->deleteSurface(tag);
    deleteFigure(tag);
}

void Facade::deleteFigure(const std::string &tag) {
    scene_manager_->getScene()->deleteFigure(tag);
}

void Facade::drawScene() {
    scene_manager_->drawScene();
}

bool Facade::hasChanges()  {
    return has_changes_;
}

void Facade::hideFigure(const std::string &tag, bool hidden) {
    if (scene_manager_->getScene()->containsFigure(tag)) {
        scene_manager_->getScene()->getFigure(tag)->getSessionState()->setHidden(hidden);
    }
}

void Facade::hideSurface(const std::string &tag, bool hidden) {
    if (scene_manager_->getScene()->containsSurface(tag)) {
        scene_manager_->getScene()->getFigure(tag)->getSessionState()->setHidden(hidden);
    }
}

bool Facade::isValid() {
    return file_manager_ != nullptr && scene_manager_ != nullptr;
}

Scene Facade::loadScene(const std::string &path) {
    Scene scene = file_manager_->read(path);
    scene_manager_->updateScene(scene);
    return scene;
}

void Facade::moveFigure(const std::string &tag, double x, double y, double z) {
    scene_manager_->getScene()->
            transformFigure(tag, TransformMatrixBuilder::createMovementMatrix(x, y, z));
}

void Facade::rotateFigure(const std::string &tag, double x, double y, double z) {
    scene_manager_->getScene()->
            transformFigure(tag, TransformMatrixBuilder::createRotationMatrix(x, y, z));
}

void Facade::scaleFigure(const std::string &tag, double x, double y, double z) {
    scene_manager_->getScene()->
            transformFigure(tag, TransformMatrixBuilder::createScalingMatrix(x, y, z));
}

std::vector<std::string> Facade::getSurfacesTags() {
    std::vector<std::string> tags;
    for (auto tag : scene_manager_->getScene()->getSurfacesTags()) {
        tags.push_back(*tag);
    }
    return tags;
}

std::shared_ptr<obj3d::Surface> Facade::getSurface(const std::string &tag) {
    return scene_manager_->getScene()->getSurface(tag);
}

std::vector<std::string> Facade::getFiguresTags() {
    std::vector<std::string> tags;
    for (auto tag : scene_manager_->getScene()->getFiguresTags()) {
        tags.push_back(*tag);
    }
    return tags;
}

std::shared_ptr<obj3d::Figure> Facade::getFigure(const std::string &tag) {
    return scene_manager_->getScene()->getFigure(tag);
}

void Facade::recalculateSurface(const std::string &surface_tag) {
    scene_manager_->getScene()->appendFigure(obj3d::Figure(*getSurface(surface_tag)));
}

void Facade::redrawScene() {
    scene_manager_->redrawScene();
}

void Facade::saveFigure(const std::string &tag, const std::string &path) {
    std::shared_ptr<obj3d::Figure> figure = getFigure(tag);
    figure->getMeta()->setPath(path);
    file_manager_->saveFigure(figure);
}
