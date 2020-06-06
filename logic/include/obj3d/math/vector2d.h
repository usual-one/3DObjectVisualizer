#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <vector>

#include "logic/include/obj3d/math/point2d.h"
#include "logic/include/obj3d/math/vector3d.h"

namespace obj3d {
    class Vector2D;
}

class obj3d::Vector2D : obj3d::Point2D {
public:
    Vector2D();

    Vector2D(double x, double y);

    Vector2D(const obj3d::Vector3D &vec);
};

#endif // VECTOR2D_H
