#include "config.h"
#include "logic/include/obj3d/figure/components/vertex3d.h"

obj3d::Vertex3D::Vertex3D(const obj3d::Vector3D &pos, size_t id) :
    id_(id) {
    setPosition(pos);
}

obj3d::Vertex3D::Vertex3D(const obj3d::Vector3D &pos, size_t id, /*const std::string &tag,*/
                      const std::set<std::shared_ptr<obj3d::Vertex3D>> connections) :
    id_(id) {
    setPosition(pos);
    setConnections(connections);
}

size_t obj3d::Vertex3D::getID() const {
    return id_;
}

std::shared_ptr<obj3d::Vector3D> obj3d::Vertex3D::getPosition() {
    return pos_;
}

std::set<size_t> obj3d::Vertex3D::getConnections() {
    return connections_;
}

void obj3d::Vertex3D::setPosition(const obj3d::Vector3D &pos) {
    pos_ = std::make_shared<obj3d::Vector3D>(pos);
}

void obj3d::Vertex3D::setConnections(const std::set<std::shared_ptr<obj3d::Vertex3D>> &connections) {
    connections_.clear();
    for (auto connection : connections) {
        addConnection(connection);
    }
}

void obj3d::Vertex3D::addConnection(std::shared_ptr<obj3d::Vertex3D> connection) {
    connections_.insert(connection->getID());
}

bool obj3d::Vertex3D::operator==(const obj3d::Vertex3D &other) {
    return getID() == other.getID();
}

bool obj3d::Vertex3D::operator!=(const obj3d::Vertex3D &other) {
    return !(*this == other);
}

void obj3d::Vertex3D::transform(const obj3d::Matrix &transform_matr) {
    pos_->transform(transform_matr);
}
