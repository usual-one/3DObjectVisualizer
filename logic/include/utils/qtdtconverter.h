#ifndef QTDTCONVERTER_H
#define QTDTCONVERTER_H

#include <QPointF>

#include "logic/include/obj3d/math/point2d.h"

class QtDTConverter {
public:
    static QPointF toQPointF(obj3d::Point2D &pt);

};

#endif // QTDTCONVERTER_H
