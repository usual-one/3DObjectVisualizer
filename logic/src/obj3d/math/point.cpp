#include "logic/include/obj3d/math/point.h"


obj3d::Point::Point() :
    x_(0) {}

obj3d::Point::Point(double x) :
    x_(x) {}

double obj3d::Point::getX() const {
    return x_;
}

void obj3d::Point::setX(double x) {
    x_ = x;
}
