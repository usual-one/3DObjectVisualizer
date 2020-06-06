#include <cmath>

#include "config.h"
#include "logic/include/scene/drawer/scenedrawer.h"

SceneDrawer::SceneDrawer(QLabel *wdg) :
    canvas_(std::make_unique<Canvas>()),
    wdg_(wdg) {}

void SceneDrawer::drawFigures(const std::vector<std::shared_ptr<CanvasFigure>> &figures,
                              const std::shared_ptr<obj3d::Rectangle2D> scope) {
    updateCanvas();
    canvas_->setBackgroundColor(BACKGROUND_COLOR);
    canvas_->setPenColor(PEN_COLOR);
    double segment = calculateSegment(scope);
    obj3d::Rectangle2D canvas_scope = calculateScope(segment);
    for (auto figure : figures) {
        drawFigure(figure, canvas_scope, segment);
    }
    wdg_->setPixmap(*canvas_->getPixmap());
}

void SceneDrawer::drawEdge(CanvasEdge &edge, const obj3d::Rectangle2D &scope, double segment) {
    if (!(scope.isInside(*edge.getBegin()) && scope.isInside(*edge.getEnd()))) {
        return;
    }
    obj3d::Point2D begin = calculateCanvasPoint(*edge.getBegin(), segment);
    obj3d::Point2D end = calculateCanvasPoint(*edge.getEnd(), segment);
    canvas_->drawLine(begin, end);
}

void SceneDrawer::drawFigure(const std::shared_ptr<CanvasFigure> &figure,
                             const obj3d::Rectangle2D &scope, double segment) {
    for (auto edge : figure->getEdges()) {
        drawEdge(*edge, scope, segment);
    }
    for (auto vertex : figure->getVertices()) {
        drawVertex(*vertex, scope, segment);
    }
}

void SceneDrawer::drawVertex(CanvasVertex &vertex, const obj3d::Rectangle2D &scope, double segment) {
    if (!scope.isInside(*vertex.getPosition())) {
        return;
    }
    obj3d::Point2D center = calculateCanvasPoint(*vertex.getPosition(), segment);
    canvas_->drawCircle(center, DEFAULT_DOT_RADIUS);
}

void SceneDrawer::updateCanvas() {
    canvas_->update(wdg_->size());
}

double SceneDrawer::calculateSegment(const std::shared_ptr<obj3d::Rectangle2D> camera_scope) {
    double plot_width = fabs(camera_scope->getRightBottom()->getX() -
                             camera_scope->getLeftBottom()->getX());
    double plot_height = fabs(camera_scope->getLeftTop()->getY() -
                              camera_scope->getLeftBottom()->getY());
    double plot_ratio = plot_width / plot_height;
    double canvas_ratio = (double) canvas_->getWidth() / (double) canvas_->getHeight();
    if (plot_ratio > canvas_ratio) {
        return (canvas_->getWidth() - 2 * CANVAS_MARGIN) / plot_width;
    } else {
        return (canvas_->getHeight() - 2 * CANVAS_MARGIN) / plot_height;
    }
}

obj3d::Point2D SceneDrawer::calculateCanvasPoint(const obj3d::Point2D &pt, double segment) {
    double x = CANVAS_MARGIN + segment * pt.getX();
    double y = canvas_->getHeight() - CANVAS_MARGIN - segment * pt.getY();
    return obj3d::Point2D(x, y);
}

obj3d::Rectangle2D SceneDrawer::calculateScope(double segment) {
    obj3d::Point2D lb(0, 0);
    obj3d::Point2D lt(0, (canvas_->getHeight() - 2 * CANVAS_MARGIN) / segment);
    obj3d::Point2D rb((canvas_->getWidth() - 2 * CANVAS_MARGIN) / segment, 0);
    obj3d::Point2D rt(rb.getX(), lt.getY());
    return obj3d::Rectangle2D(lb, lt, rb, rt);
}
