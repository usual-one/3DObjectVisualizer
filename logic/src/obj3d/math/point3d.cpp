#include "logic/include/obj3d/math/point3d.h"


obj3d::Point3D::Point3D() :
    Point2D(),
    z_(0) {}

obj3d::Point3D::Point3D(double x, double y, double z) :
    Point2D(x, y),
    z_(z) {}

double obj3d::Point3D::getZ() const {
    return z_;
}

void obj3d::Point3D::setZ(double z) {
    z_ = z;
}

obj3d::Point2D obj3d::Point3D::toPoint2D() const {
    return obj3d::Point2D(x_, y_);
}

bool obj3d::Point3D::operator==(const obj3d::Point3D &other) {
    return isEqualTo(other);
}

bool obj3d::Point3D::operator!=(const obj3d::Point3D &other) {
    return !isEqualTo(other);
}

bool obj3d::Point3D::isEqualTo(const obj3d::Point3D &other) {
    return x_ == other.x_ && y_ == other.y_ && z_ == other.z_;
}
