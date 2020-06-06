#ifndef BASESCENEDRAWER_H
#define BASESCENEDRAWER_H

#include "logic/include/scene/constructor/figure/canvasfigure.h"
#include "logic/include/obj3d/math/rectangle2d.h"

class BaseSceneDrawer {
public:
    virtual void drawFigures(const std::vector<std::shared_ptr<CanvasFigure>> &figures,
                             const std::shared_ptr<obj3d::Rectangle2D> scope) = 0;

};

#endif // BASESCENEDRAWER_H
