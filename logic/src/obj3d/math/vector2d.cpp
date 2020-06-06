#include "logic/include/obj3d/math/vector2d.h"

obj3d::Vector2D::Vector2D() :
    obj3d::Point2D(0, 0) {}

obj3d::Vector2D::Vector2D(double x, double y) :
    obj3d::Point2D(x, y) {}

obj3d::Vector2D::Vector2D(const obj3d::Vector3D &vec) :
    obj3d::Point2D(vec.getX(), vec.getY()) {}
