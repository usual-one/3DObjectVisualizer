#ifndef CANVASVERTEX_H
#define CANVASVERTEX_H

#include <memory>
#include <string>

#include "logic/include/obj3d/math/point2d.h"
#include "logic/include/obj3d/figure/components/vertex3d.h"
#include "logic/include/scene/constructor/camera.h"

class CanvasVertex {
public:
    CanvasVertex(obj3d::Vertex3D &vertex, Camera &camera);

    size_t getID() const;

    std::shared_ptr<obj3d::Point2D> getPosition();

private:
    size_t unique_id_;

    std::shared_ptr<obj3d::Point2D> pos_;

};

#endif // CANVASVERTEX_H
