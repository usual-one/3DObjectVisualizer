#include "config.h"
#include "logic/include/obj3d/figure/components/vertex3d.h"

size_t obj3d::Vertex3D::count_ = 0;

obj3d::Vertex3D::Vertex3D(const obj3d::Vector3D &pos) {
    count_++;
    setPosition(pos);
    setTag(DEFAULT_VERTEX_TAG + std::to_string(count_));
}

obj3d::Vertex3D::Vertex3D(const obj3d::Vector3D &pos, const std::string &tag) {
    count_++;
    setPosition(pos);
    setTag(tag);
}

obj3d::Vertex3D::Vertex3D(const obj3d::Vector3D &pos, const std::string &tag,
                      const std::set<std::shared_ptr<obj3d::Vertex3D>> connections) {
    count_++;
    setPosition(pos);
    setTag(tag);
    setConnections(connections);
}

std::shared_ptr<obj3d::Vector3D> obj3d::Vertex3D::getPosition() {
    return pos_;
}

std::shared_ptr<std::string> obj3d::Vertex3D::getTag() {
    return tag_;
}

std::set<std::string> obj3d::Vertex3D::getConnections() {
    return connections_;
}

void obj3d::Vertex3D::setPosition(const obj3d::Vector3D &pos) {
    pos_ = std::make_shared<obj3d::Vector3D>(pos);
}

void obj3d::Vertex3D::setTag(const std::string &tag) {
    tag_ = std::make_shared<std::string>(tag);
}

void obj3d::Vertex3D::setConnections(const std::set<std::shared_ptr<obj3d::Vertex3D>> &connections) {
    connections_.clear();
    for (auto connection : connections) {
        addConnection(connection);
    }
}

void obj3d::Vertex3D::addConnection(std::shared_ptr<obj3d::Vertex3D> connection) {
    connections_.insert(*connection->getTag());
}

bool obj3d::Vertex3D::operator==(const obj3d::Vertex3D &other) {
    return *tag_ == *other.tag_;
}

bool obj3d::Vertex3D::operator!=(const obj3d::Vertex3D &other) {
    return !(*this == other);
}

void obj3d::Vertex3D::transform(const obj3d::Matrix &transform_matr) {
    pos_->transform(transform_matr);
}
