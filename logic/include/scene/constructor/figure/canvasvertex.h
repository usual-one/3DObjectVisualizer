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

    std::shared_ptr<std::string> getTag();

    std::shared_ptr<obj3d::Point2D> getPosition();

private:
    std::shared_ptr<std::string> tag_;

    std::shared_ptr<obj3d::Point2D> pos_;

};

#endif // CANVASVERTEX_H
