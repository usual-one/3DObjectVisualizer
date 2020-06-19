#ifndef SCENEDRAWER_H
#define SCENEDRAWER_H

#include <QLabel>

#include "logic/include/scene/drawer/basescenedrawer.h"
#include "logic/include/scene/drawer/canvas.h"

class SceneDrawer : public BaseSceneDrawer {
public:
    SceneDrawer() = delete;

    SceneDrawer(QLabel *wdg);

    void drawFigures(const std::vector<std::shared_ptr<CanvasFigure>> &figures,
                     const std::shared_ptr<obj3d::Rectangle2D> scope) override;

    void updateCanvas();

private:
    void drawEdge(CanvasEdge &edge, const obj3d::Rectangle2D &scope, double segment);

    void drawFigure(const std::shared_ptr<CanvasFigure> &figure,
                    const obj3d::Rectangle2D &scope, double segment);

    void drawVertex(CanvasVertex &vertex, const obj3d::Rectangle2D &scope, double segment);

    double calculateSegment(const std::shared_ptr<obj3d::Rectangle2D> camera_scope);

    obj3d::Point2D calculateCanvasPoint(const obj3d::Point2D &pt, double segment);

    obj3d::Rectangle2D calculateScope(double segment);

    std::unique_ptr<Canvas> canvas_;

    QLabel *wdg_;

};

#endif // SCENEDRAWER_H
