#include "logic/include/scene/constructor/figure/canvasedge.h"

CanvasEdge::CanvasEdge(const obj3d::Point2D &begin, const obj3d::Point2D &end) :
    begin_(std::make_shared<obj3d::Point2D>(begin)),
    end_(std::make_shared<obj3d::Point2D>(end)) {}

std::shared_ptr<obj3d::Point2D> CanvasEdge::getBegin() {
    return begin_;
}

std::shared_ptr<obj3d::Point2D> CanvasEdge::getEnd() {
    return end_;
}
