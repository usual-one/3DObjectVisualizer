#ifndef CANVASFIGURE_H
#define CANVASFIGURE_H

#include "logic/include/obj3d/figure/figure3d.h"
#include "logic/include/scene/constructor/figure/canvasvertex.h"
#include "logic/include/scene/constructor/figure/canvasedge.h"

class CanvasFigure {
public:
    CanvasFigure(obj3d::Figure &figure, Camera &camera);

    std::shared_ptr<CanvasVertex> getVertex(const std::string &tag);

    void changeOrigin(const obj3d::Point2D &origin);

    std::vector<std::shared_ptr<CanvasEdge>> getEdges();

    std::vector<std::shared_ptr<CanvasVertex>> getVertices();

    std::vector<obj3d::Point2D> toPoints();

private:
    void calculateEdges(const std::set<std::shared_ptr<obj3d::Edge>> &edges);

    std::vector<std::shared_ptr<CanvasVertex>> vertices_;

    std::vector<std::shared_ptr<CanvasEdge>> edges_;

};

#endif // CANVASFIGURE_H
