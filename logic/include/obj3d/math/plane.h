#ifndef PLANE_H
#define PLANE_H

#include "logic/include/obj3d/math/vector3d.h"


namespace obj3d {
    class Plane;
}


class obj3d::Plane {
public:
    Plane();

    Plane(const obj3d::Vector3D &normal, double d);

    Plane(const obj3d::Point3D &p1, const obj3d::Point3D &p2, const obj3d::Point3D &p3);

    Plane(const obj3d::Vector3D &vec1, const obj3d::Vector3D &vec2);

    obj3d::Vector3D getNormal();

    double getD();

    obj3d::Point3D projectPoint(const obj3d::Point3D &point);

    void moveFromOrigin(double dist);

private:
    obj3d::Vector3D normal_;

    double d_;
};


#endif // PLANE_H
