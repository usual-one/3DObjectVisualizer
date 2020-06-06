#include "config.h"
#include "logic/include/obj3d/math/exception/pointexception.h"
#include "logic/include/obj3d/math/point2d.h"


obj3d::Point2D::Point2D() :
    Point(),
    y_(0) {}

obj3d::Point2D::Point2D(double x, double y) :
    Point(x),
    y_(y) {}

double obj3d::Point2D::getY() const {
    return y_;
}

void obj3d::Point2D::setY(double y) {
    y_ = y;
}

void obj3d::Point2D::changeOrigin(const obj3d::Point2D &origin) {
    x_ -= origin.getX();
    y_ -= origin.getY();
}

double obj3d::Point2D::getMaxX(const std::vector<obj3d::Point2D> &points) {
    if (!points.size()) {
        throw PointException(EMPTY_VECTOR_MESSAGE);
    }
    double max_x = points[0].getX();
    for (auto point : points) {
        if (point.getX() > max_x) {
            max_x = point.getX();
        }
    }
    return max_x;
}

double obj3d::Point2D::getMaxY(const std::vector<obj3d::Point2D> &points) {
    if (!points.size()) {
        throw PointException(EMPTY_VECTOR_MESSAGE);
    }
    double max_y = points[0].getY();
    for (auto point : points) {
        if (point.getY() > max_y) {
            max_y = point.getY();
        }
    }
    return max_y;
}

double obj3d::Point2D::getMinY(const std::vector<obj3d::Point2D> &points) {
    if (!points.size()) {
       throw PointException(EMPTY_VECTOR_MESSAGE);
    }
    double min_y = points[0].getY();
    for (auto point : points) {
       if (point.getY() < min_y) {
           min_y = point.getY();
       }
    }
    return min_y;
}

double obj3d::Point2D::getMinX(const std::vector<obj3d::Point2D> &points) {
    if (!points.size()) {
       throw PointException(EMPTY_VECTOR_MESSAGE);
    }
    double min_x = points[0].getX();
    for (auto point : points) {
       if (point.getX() < min_x) {
           min_x = point.getX();
       }
    }
    return min_x;
}
