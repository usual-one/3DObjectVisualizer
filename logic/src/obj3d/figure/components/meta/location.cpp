#include "logic/include/obj3d/figure/components/meta/location.h"

Location::Location() :
    movement_(std::make_shared<obj3d::Point3D>(0, 0, 0)),
    rotation_(std::make_shared<obj3d::Point3D>(0, 0, 0)),
    scaling_(std::make_shared<obj3d::Point3D>(1, 1, 1)) {}

std::shared_ptr<obj3d::Point3D> Location::getMovement() {
    return movement_;
}

std::shared_ptr<obj3d::Point3D> Location::getRotation() {
    return rotation_;
}

std::shared_ptr<obj3d::Point3D> Location::getScaling() {
    return scaling_;
}

void Location::copy(const Location &other) {
    *movement_ = *other.movement_;
    *rotation_ = *other.rotation_;
    *scaling_ = *other.scaling_;
}
