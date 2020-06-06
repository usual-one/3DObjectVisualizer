#include "logic/include/scene/constructor/camera.h"

Camera::Camera() :
    scope_(nullptr) {
    calculatePlane();
    calculateBasis();
}

Camera::Camera(const obj3d::Plane &plane) :
    plane_(std::make_shared<obj3d::Plane>(plane)),
    scope_(nullptr) {
    calculateBasis();
}

bool Camera::hasScope() {
    return scope_ != nullptr;
}

std::shared_ptr<obj3d::Rectangle2D> Camera::calculateScope(const std::vector<obj3d::Point2D> &projected_points) {
    if (!hasScope()) {
        scope_ = std::make_shared<obj3d::Rectangle2D>();
    }
    *scope_->getLeftBottom() = obj3d::Point2D(obj3d::Point2D::getMinX(projected_points),
                                             obj3d::Point2D::getMinY(projected_points));
    *scope_->getLeftTop() = obj3d::Point2D(scope_->getLeftBottom()->getX(),
                                          obj3d::Point2D::getMaxY(projected_points));
    *scope_->getRightBottom() = obj3d::Point2D(obj3d::Point2D::getMaxX(projected_points),
                                              scope_->getLeftBottom()->getY());
    *scope_->getRightTop() = obj3d::Point2D(scope_->getLeftBottom()->getX(),
                                          scope_->getLeftTop()->getY());
    return getScope();
}

std::shared_ptr<obj3d::Rectangle2D> Camera::getScope() {
    return scope_;
}

std::shared_ptr<obj3d::Plane> Camera::getPlane() {
    return plane_;
}

std::shared_ptr<obj3d::Basis3D> Camera::getBasis() {
    return basis_;
}

void Camera::calculateBasis() {
    obj3d::Vector3D k(plane_->getNormal());
    obj3d::Vector3D j(plane_->projectPoint(obj3d::Point3D(0, 0, 0)),
                      plane_->projectPoint(obj3d::Point3D(0, 0, 1)));
    obj3d::Vector3D i(obj3d::Plane(j, k).getNormal());
    basis_ = std::make_shared<obj3d::Basis3D>(i, j, k);
}

void Camera::calculatePlane() {
    plane_ = std::make_shared<obj3d::Plane>(obj3d::Vector3D(-1, -1, -1), 0);
}
