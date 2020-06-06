#ifndef POINT3D_H
#define POINT3D_H

#include "logic/include/obj3d/math/point2d.h"


namespace obj3d {
    class Point3D;
}


class obj3d::Point3D : public obj3d::Point2D {
public:
    Point3D();

    Point3D(double x, double y, double z);

    double getZ() const;

    void setZ(double z);

    obj3d::Point2D toPoint2D() const;

    bool operator==(const obj3d::Point3D &other);

    bool operator!=(const obj3d::Point3D &other);

protected:
    bool isEqualTo(const obj3d::Point3D &other);

    double z_;

};


#endif // POINT3D_H
