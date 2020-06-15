#include "config.h"
#include "logic/include/obj3d/figure/components/vertex.h"

obj3d::Vertex::Vertex(const obj3d::Vector3D &pos, size_t id) :
    id_(id) {
    setPosition(pos);
}

obj3d::Vertex::Vertex(const obj3d::Vector3D &pos, size_t id, /*const std::string &tag,*/
                      const std::set<std::shared_ptr<obj3d::Vertex>> connections) :
    id_(id) {
    setPosition(pos);
    setConnections(connections);
}

size_t obj3d::Vertex::getID() const {
    return id_;
}

std::shared_ptr<obj3d::Vector3D> obj3d::Vertex::getPosition() {
    return pos_;
}

std::set<size_t> obj3d::Vertex::getConnections() {
    return connections_;
}

bool obj3d::Vertex::isConnected(size_t id) {
    for (auto connection : connections_) {
        if (connection == id) {
            return true;
        }
    }
    return false;
}

void obj3d::Vertex::setPosition(const obj3d::Vector3D &pos) {
    pos_ = std::make_shared<obj3d::Vector3D>(pos);
}

void obj3d::Vertex::setConnections(const std::set<size_t> &connections) {
    connections_.clear();
    for (auto connection : connections) {
        addConnection(connection);
    }
}

void obj3d::Vertex::setConnections(const std::set<std::shared_ptr<obj3d::Vertex>> &connections) {
    connections_.clear();
    for (auto connection : connections) {
        addConnection(connection);
    }
}

void obj3d::Vertex::addConnection(std::shared_ptr<obj3d::Vertex> connection) {
    addConnection(connection->getID());
}

void obj3d::Vertex::addConnection(size_t id) {
    if (isConnected(id)) {
        return;
    }
    connections_.insert(id);
}

bool obj3d::Vertex::operator==(const obj3d::Vertex &other) {
    return getID() == other.getID();
}

bool obj3d::Vertex::operator!=(const obj3d::Vertex &other) {
    return !(*this == other);
}

void obj3d::Vertex::transform(const obj3d::Matrix &transform_matr) {
    pos_->transform(transform_matr);
}
