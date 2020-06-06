#ifndef CANVAS_H
#define CANVAS_H

#include "logic/include/obj3d/math/point2d.h"

#include <QPixmap>
#include <QPainter>

class Canvas {
public:
    Canvas();

    Canvas(const QSize &size);

    ~Canvas();

    QPixmap *getPixmap();

    QPainter *getPainter();

    size_t getWidth();

    size_t getHeight();

    bool isInside(const obj3d::Point2D &pt);

    bool isValid();

    void setBackgroundColor(const QColor &color);

    void setPenColor(const QColor &color);

    void drawLine(obj3d::Point2D &begin, obj3d::Point2D &end);

    void drawCircle(obj3d::Point2D &center, double radius);

    void update(const QSize &size);

private:
    void create(const QSize &size);

    void clear();

    void setAntialiasing();

    QPixmap *pixmap_;

    QPainter *painter_;
};

#endif // CANVAS_H
