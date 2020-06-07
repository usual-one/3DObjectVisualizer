#include "logic/include/obj3d/figure/figure3d.h"
#include "config.h"

size_t obj3d::Figure::count_ = 0;

obj3d::Figure::Figure() :
    meta_(std::make_shared<FigureMeta>()) {
    count_++;
    createDefaultTag();
}

obj3d::Figure::Figure(obj3d::Surface &surface) :
    meta_(std::make_shared<FigureMeta>()) {
    count_++;
    tag_ = surface.getTag();
    vertices_ = surface.toVertices();
    setEdges();
}

void obj3d::Figure::addEdge(std::shared_ptr<obj3d::Edge> edge) {
    if (contains(*edge)) {
        return;
    }
    edges_.insert(edge);
}

void obj3d::Figure::addVertex(std::shared_ptr<obj3d::Vertex3D> vertex) {
    if (contains(*vertex)) {
        return;
    }
    vertices_.insert(vertex);
}

bool obj3d::Figure::contains(const obj3d::Edge &edge) {
    for (auto existing_edge : edges_) {
        if (*existing_edge == edge) {
            return true;
        }
    }
    return false;
}

bool obj3d::Figure::contains(const obj3d::Vertex3D vertex) {
    for (auto existing_vertex : vertices_) {
        if (*existing_vertex == vertex) {
            return true;
        }
    }
    return false;
}

void obj3d::Figure::transform(const Matrix &transform_matr) {
    for (auto vertex : vertices_) {
        vertex->transform(transform_matr);
    }
}

std::set<std::shared_ptr<obj3d::Vertex3D>> obj3d::Figure::getVertices() {
    return vertices_;
}

std::set<std::shared_ptr<obj3d::Edge>> obj3d::Figure::getEdges() {
    return edges_;
}

std::shared_ptr<obj3d::Vertex3D> obj3d::Figure::getVertex(size_t id) {
    for (auto vertex : vertices_) {
        if (vertex->getID() == id) {
            return vertex;
        }
    }
    return nullptr;
}

std::shared_ptr<Location> obj3d::Figure::getLocation() {
    return meta_->getLocation();
}

std::shared_ptr<FigureMeta> obj3d::Figure::getMeta() {
    return meta_;
}

obj3d::Point3D obj3d::Figure::getAverageLocation() {
    double sum_x = 0;
    double sum_y = 0;
    double sum_z = 0;

    for (auto vertex : vertices_) {
        sum_x += vertex->getPosition()->getX();
        sum_y += vertex->getPosition()->getY();
        sum_z += vertex->getPosition()->getZ();
    }
    return obj3d::Point3D(sum_x / vertices_.size(), sum_y / vertices_.size(), sum_z / vertices_.size());
}

void obj3d::Figure::createDefaultTag() {
    tag_ = std::make_shared<std::string>(DEFAULT_FIGURE_TAG + std::to_string(count_));
}

void obj3d::Figure::setEdges() {
    edges_.clear();
    for (auto vertex : vertices_) {
        for (auto connection : vertex->getConnections()) {
            obj3d::Edge new_edge(vertex->getID(), connection);
            if (!contains(new_edge)) {
                edges_.insert(std::make_shared<obj3d::Edge>(new_edge));
            }
        }
    }
}
