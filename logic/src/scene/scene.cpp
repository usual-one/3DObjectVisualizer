#include <algorithm>

#include "logic/include/scene/scene.h"
#include "logic/include/scene/exception/unknowntagexception.h"
#include "config.h"

Scene::Scene() {
    figures_.clear();
    surfaces_.clear();
}

void Scene::appendSurface(std::shared_ptr<obj3d::Surface> surface) {
    surfaces_.push_back(surface);
}

void Scene::appendFigure(std::shared_ptr<obj3d::Figure> figure) {
    if (isFigureTag(*figure->getTag())) {
        deleteFigure(*figure->getTag());
    }
    figures_.push_back(figure);
}

void Scene::appendFigure(obj3d::Figure figure) {
    appendFigure(std::make_shared<obj3d::Figure>(figure));
}

bool Scene::containsSurface(const std::string &tag) {
    for (auto surface_tag : getSurfacesTags()) {
        if (*surface_tag == tag) {
            return true;
        }
    }
    return false;
}

bool Scene::containsFigure(const std::string &tag) {
    for (auto figure_tag : getFiguresTags()) {
        if (*figure_tag == tag) {
            return true;
        }
    }
    return false;
}

void Scene::deleteFigure(const std::string &tag) {
    figures_.erase(std::find(figures_.begin(), figures_.end(), getFigure(tag)));
}

void Scene::deleteSurface(const std::string &tag) {
    surfaces_.erase(std::find(surfaces_.begin(), surfaces_.end(), getSurface(tag)));
}

bool Scene::isFigureTag(const std::string &tag) {
    for (auto figure : figures_) {
        if (*figure->getTag() == tag) {
            return true;
        }
    }
    return false;
}

std::vector<std::shared_ptr<std::string>> Scene::getSurfacesTags() {
    std::vector<std::shared_ptr<std::string>> tags = {};
    for (auto surface : surfaces_) {
        tags.push_back(surface->getTag());
    }
    return tags;
}

std::vector<std::shared_ptr<std::string>> Scene::getFiguresTags() {
    std::vector<std::shared_ptr<std::string>> tags = {};
    for (auto figure : figures_) {
        tags.push_back(figure->getTag());
    }
    return tags;
}

std::shared_ptr<obj3d::Surface> Scene::getSurface(const std::string &tag) {
    for (auto surface : surfaces_) {
        if (*surface->getTag() == tag) {
            return surface;
        }
    }
    throw UnknownTagException(UNKNOWN_TAG_MESSAGE, tag);
}

std::shared_ptr<obj3d::Figure> Scene::getFigure(const std::string &tag) {
    for (auto figure : figures_) {
        if (*figure->getTag() == tag) {
            return figure;
        }
    }
    throw UnknownTagException(UNKNOWN_TAG_MESSAGE, tag);
}

void Scene::update(const Scene &other) {
    std::vector<std::shared_ptr<std::string>> figure_tags = getFiguresTags();
    for (auto figure : other.figures_) {
        if (std::find(figure_tags.begin(), figure_tags.end(), figure->getTag()) == figure_tags.end()) {
            figures_.push_back(figure);
        }
    }
    std::vector<std::shared_ptr<std::string>> surface_tags = getSurfacesTags();
    for (auto surface : other.surfaces_) {
        if (std::find(surface_tags.begin(), surface_tags.end(), surface->getTag()) == surface_tags.end()) {
            surfaces_.push_back(surface);
        }
    }
}
