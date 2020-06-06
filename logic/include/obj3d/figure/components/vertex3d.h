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

    Vertex3D(const obj3d::Vector3D &pos);

    Vertex3D(const obj3d::Vector3D &pos, const std::string &tag);

    Vertex3D(const obj3d::Vector3D &pos, const std::string &tag,
           const std::set<std::shared_ptr<obj3d::Vertex3D>> connections);

    std::shared_ptr<obj3d::Vector3D> getPosition();

    std::shared_ptr<std::string> getTag();

    std::set<std::string> getConnections();

    void setPosition(const obj3d::Vector3D &pos);

    void setTag(const std::string &tag);

    void setConnections(const std::set<std::shared_ptr<obj3d::Vertex3D>> &connections);

    void addConnection(std::shared_ptr<obj3d::Vertex3D> connection);

    bool operator==(const obj3d::Vertex3D &other);

    bool operator!=(const obj3d::Vertex3D &other);

    void transform(const obj3d::Matrix &transform_matr);

private:
    static size_t count_;

    std::shared_ptr<std::string> tag_;

    std::shared_ptr<obj3d::Vector3D> pos_;

    std::set<std::string> connections_;
};

#endif // VERTEX_H
