#ifndef LOCATION_H
#define LOCATION_H

#include <memory>

#include "logic/include/obj3d/math/vector3d.h"

class State {
public:
    State();

    std::shared_ptr<obj3d::Vector3D> getMovement();

    std::shared_ptr<obj3d::Vector3D> getRotation();

    std::shared_ptr<obj3d::Vector3D> getScaling();

    void copy(const State &other);

private:

    std::shared_ptr<obj3d::Vector3D> movement_;

    std::shared_ptr<obj3d::Vector3D> rotation_;

    std::shared_ptr<obj3d::Vector3D> scaling_;

};

#endif // LOCATION_H
