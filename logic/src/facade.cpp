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

const std::string &Facade::addNewFigure() {
    obj3d::Figure figure;
    scene_manager_->getScene()->appendFigure(figure);
    return figure.getTag();
}

void Facade::deleteSurface(const std::string &tag) {
    scene_manager_->getScene()->deleteSurface(tag);
    scene_manager_->getScene()->deleteFigure(tag);
}

void Facade::deleteFigure(const std::string &tag) {
    if (scene_manager_->getScene()->getFigure(tag)->getSessionState()->isSurface()) {
        scene_manager_->getScene()->deleteSurface(tag);
    }
    scene_manager_->getScene()->deleteFigure(tag);
}

void Facade::drawScene() {
    scene_manager_->drawScene();
}

bool Facade::hasUnsaved()  {
    for (auto tag : getFiguresTags()) {
        if (!getFigure(tag)->getMeta()->isSaved()) {
            return true;
        }
    }
    return false;
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

std::vector<std::string> Facade::getSurfacesTags() {
    std::vector<std::string> tags;
    for (auto tag : scene_manager_->getScene()->getSurfacesTags()) {
        tags.push_back(tag);
    }
    return tags;
}

std::shared_ptr<obj3d::Surface> Facade::getSurface(const std::string &tag) {
    return scene_manager_->getScene()->getSurface(tag);
}

std::vector<std::string> Facade::getFiguresTags() {
    std::vector<std::string> tags;
    for (auto tag : scene_manager_->getScene()->getFiguresTags()) {
        tags.push_back(tag);
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
    figure->getMeta()->setSaved(true);
    file_manager_->saveFigure(figure);
}

void Facade::updateFigureVertices(const std::string &tag, std::shared_ptr<FigureVerticesDTO> vertices) {
    std::shared_ptr<obj3d::Figure> figure = getFigure(tag);
    figure->updateVertices(vertices);
    figure->getMeta()->setSaved(false);
}

void Facade::updateFigureSessionState(const std::string &tag, std::shared_ptr<SessionStateDTO> state) {
    std::shared_ptr<obj3d::Figure> figure = getFigure(tag);
    figure->updateSessionState(state);
    if (figure->getSessionState()->isSurface()) {
        getSurface(tag)->setTag(state->getTag());
    }
}

void Facade::updateFigureState(const std::string tag, std::shared_ptr<FigureStateDTO> state) {
    getFigure(tag)->updateState(state);
}
