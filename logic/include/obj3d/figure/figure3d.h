#ifndef FIGURE_H
#define FIGURE_H

#include <set>

#include "logic/include/obj3d/object3d.h"
#include "logic/include/obj3d/figure/components/edge.h"
#include "logic/include/obj3d/figure/components/vertex3d.h"
#include "logic/include/obj3d/surface/surface.h"
#include "logic/include/obj3d/figure/components/meta/figuremeta.h"

namespace obj3d {
    class Figure;
}

class obj3d::Figure : public obj3d::Object3D {
public:
    Figure();

    Figure(obj3d::Surface &surface);

    void addEdge(std::shared_ptr<obj3d::Edge> edge);

    void addVertex(std::shared_ptr<obj3d::Vertex3D> vertex);

    bool contains(const obj3d::Edge &edge);

    bool contains(const obj3d::Vertex3D vertex);

    void setVertices(std::shared_ptr<std::vector<obj3d::Vertex3D>> &vertices);

    void transform(const obj3d::Matrix &transform_matr);

    obj3d::Point3D getAverageLocation();

    std::set<std::shared_ptr<obj3d::Edge>> getEdges();

    std::shared_ptr<State> getLocation();

    std::shared_ptr<FigureMeta> getMeta();

    std::set<std::shared_ptr<obj3d::Vertex3D>> getVertices();

    std::vector<obj3d::Vertex3D> getVerticesVector();

    std::shared_ptr<obj3d::Vertex3D> getVertex(size_t id);

private:
    void createDefaultTag();

    void setEdges();

    static size_t count_;

    std::set<std::shared_ptr<obj3d::Vertex3D>> vertices_;

    std::set<std::shared_ptr<obj3d::Edge>> edges_;

    std::shared_ptr<FigureMeta> meta_;
};

#endif // FIGURE_H
