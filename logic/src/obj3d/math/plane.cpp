#include <cmath>

#include "logic/include/obj3d/math/plane.h"


obj3d::Plane::Plane() :
    normal_(obj3d::Vector3D()),
    d_(0) {}

obj3d::Plane::Plane(const obj3d::Vector3D &normal, double d) :
    normal_(normal),
    d_(d) {}

obj3d::Plane::Plane(const obj3d::Point3D &p1, const obj3d::Point3D &p2, const obj3d::Point3D &p3) {
    normal_ = obj3d::Vector3D(p1, p2) * obj3d::Vector3D(p1, p3);
    d_ = -(normal_.getX() * p1.getX() + normal_.getY() * p1.getY() + normal_.getZ() * p1.getZ());
}

obj3d::Plane::Plane(const obj3d::Vector3D &vec1, const obj3d::Vector3D &vec2) :
    obj3d::Plane(vec1, vec2, obj3d::Point3D()) {}

obj3d::Vector3D obj3d::Plane::getNormal() {
    return normal_;
}

double obj3d::Plane::getD() {
    return d_;
}

obj3d::Point3D obj3d::Plane::projectPoint(const obj3d::Point3D &point) {
    obj3d::Matrix linear_system;
    linear_system.addColumn({normal_.getY(), 0, normal_.getX()});
    linear_system.addColumn({-normal_.getX(), normal_.getZ(), normal_.getY()});
    linear_system.addColumn({0, -normal_.getY(), normal_.getZ()});
    obj3d::Vector3D system_result(normal_.getY() * point.getX() - normal_.getX() * point.getY(),
                                  normal_.getZ() * point.getY() - normal_.getY() * point.getZ(),
                                  -d_);

    return obj3d::Matrix::solveLinearSystemCramer(linear_system, system_result);
}

void obj3d::Plane::moveFromOrigin(double dist) {
    obj3d::Vector3D dist_vec(normal_);
    dist_vec.changeSize(dist);
    d_ = pow(dist_vec.getX(), 2) + pow(dist_vec.getY(), 2) + pow(dist_vec.getZ(), 2);
}
