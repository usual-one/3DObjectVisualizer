#ifndef VERTEX_H
#define VERTEX_H

#include <memory>
#include <set>
#include <string>

#include "logic/include/obj3d/math/vector3d.h"
#include "logic/include/obj3d/math/plane.h"

namespace obj3d {
    class Vertex3D;
}

class obj3d::Vertex3D {
public:
    Vertex3D() = delete;

    Vertex3D(const obj3d::Vector3D &pos, size_t id);

    Vertex3D(const obj3d::Vector3D &pos, size_t id,
             const std::set<std::shared_ptr<obj3d::Vertex3D>> connections);

    size_t getID() const;

    std::shared_ptr<obj3d::Vector3D> getPosition();

    std::set<size_t> getConnections();

    bool isConnected(size_t id);

    void setPosition(const obj3d::Vector3D &pos);

    void setConnections(const std::set<size_t> &connections);

    void setConnections(const std::set<std::shared_ptr<obj3d::Vertex3D>> &connections);

    void addConnection(std::shared_ptr<obj3d::Vertex3D> connection);

    void addConnection(size_t id);

    bool operator==(const obj3d::Vertex3D &other);

    bool operator!=(const obj3d::Vertex3D &other);

    void transform(const obj3d::Matrix &transform_matr);

private:
    size_t id_;

    std::shared_ptr<obj3d::Vector3D> pos_;

    std::set<size_t> connections_;
};

#endif // VERTEX_H
