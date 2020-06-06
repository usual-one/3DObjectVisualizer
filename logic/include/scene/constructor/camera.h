#ifndef CAMERA_H
#define CAMERA_H

#include "logic/include/obj3d/math/basis3d.h"
#include "logic/include/obj3d/math/plane.h"
#include "logic/include/obj3d/math/rectangle2d.h"


class Camera {
public:
    Camera();

    Camera(const obj3d::Plane &plane);

    bool hasScope();

    std::shared_ptr<obj3d::Rectangle2D> calculateScope(
            const std::vector<obj3d::Point2D> &projected_points);

    std::shared_ptr<obj3d::Rectangle2D> getScope();

    std::shared_ptr<obj3d::Plane> getPlane();

    std::shared_ptr<obj3d::Basis3D> getBasis();

private:
    void calculateBasis();

    void calculatePlane();

    std::shared_ptr<obj3d::Basis3D> basis_;

    std::shared_ptr<obj3d::Plane> plane_;

    std::shared_ptr<obj3d::Rectangle2D> scope_;

};

#endif // CAMERA_H
