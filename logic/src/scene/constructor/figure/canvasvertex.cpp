#include "logic/include/scene/constructor/figure/canvasvertex.h"

CanvasVertex::CanvasVertex(obj3d::Vertex &vertex, Camera &camera) :
    unique_id_(vertex.getID()) {
    obj3d::Vector3D projected_vector(camera.getPlane()->projectPoint(*vertex.getPosition()));
    obj3d::Point2D expanded_pt = camera.getBasis()->expandVector(projected_vector).toPoint2D();
    pos_ = std::make_shared<obj3d::Point2D>(expanded_pt);
}

size_t CanvasVertex::getID() const {
    return unique_id_;
}


std::shared_ptr<obj3d::Point2D> CanvasVertex::getPosition() {
    return pos_;
}
