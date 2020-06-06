#ifndef CANVASEDGE_H
#define CANVASEDGE_H

#include <memory>
#include "logic/include/obj3d/figure/components/edge.h"

class CanvasEdge {
public:
    CanvasEdge(const obj3d::Point2D &begin, const obj3d::Point2D &end);

    std::shared_ptr<obj3d::Point2D> getBegin();

    std::shared_ptr<obj3d::Point2D> getEnd();

private:
    std::shared_ptr<obj3d::Point2D> begin_;

    std::shared_ptr<obj3d::Point2D> end_;

};

#endif // CANVASEDGE_H
