#ifndef LOCATION_H
#define LOCATION_H

#include <memory>

#include "logic/include/obj3d/math/point3d.h"

class State {
public:
    State();

    std::shared_ptr<obj3d::Point3D> getMovement();

    std::shared_ptr<obj3d::Point3D> getRotation();

    std::shared_ptr<obj3d::Point3D> getScaling();

    void copy(const State &other);

private:

    std::shared_ptr<obj3d::Point3D> movement_;

    std::shared_ptr<obj3d::Point3D> rotation_;

    std::shared_ptr<obj3d::Point3D> scaling_;

};

#endif // LOCATION_H
