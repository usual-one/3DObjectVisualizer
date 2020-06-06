#include "logic/include/scene/constructor/figure/canvasfigure.h"

CanvasFigure::CanvasFigure(obj3d::Figure &figure, Camera &camera) {
    for (auto vertex : figure.getVertices()) {
        vertices_.push_back(std::make_shared<CanvasVertex>(*vertex, camera));
    }
    calculateEdges(figure.getEdges());
}

std::shared_ptr<CanvasVertex> CanvasFigure::getVertex(const std::string &tag) {
    for (auto vertex : vertices_) {
        if (*vertex->getTag() == tag) {
            return vertex;
        }
    }
    return nullptr;
}

void CanvasFigure::changeOrigin(const obj3d::Point2D &origin) {
    for (auto vertex : vertices_) {
        vertex->getPosition()->changeOrigin(origin);
    }
    for (auto edge : edges_) {
        edge->getBegin()->changeOrigin(origin);
        edge->getEnd()->changeOrigin(origin);
    }
}

std::vector<std::shared_ptr<CanvasEdge>> CanvasFigure::getEdges() {
    return edges_;
}

std::vector<std::shared_ptr<CanvasVertex> > CanvasFigure::getVertices() {
    return vertices_;
}

std::vector<obj3d::Point2D> CanvasFigure::toPoints() {
    std::vector<obj3d::Point2D> pts = {};
    for (auto vertex : vertices_) {
        pts.push_back(*vertex->getPosition());
    }
    return pts;
}

void CanvasFigure::calculateEdges(const std::set<std::shared_ptr<obj3d::Edge>> &edges) {
    edges_.clear();
    for (auto edge : edges) {
        obj3d::Point2D begin = *getVertex(*edge->getBegin())->getPosition();
        obj3d::Point2D end = *getVertex(*edge->getEnd())->getPosition();
        edges_.push_back(std::make_shared<CanvasEdge>(begin, end));
    }
}
