#include "logic/include/utils/qtdtconverter.h"

QPointF QtDTConverter::toQPointF(obj3d::Point2D &pt) {
    return QPointF(pt.getX(), pt.getY());
}
