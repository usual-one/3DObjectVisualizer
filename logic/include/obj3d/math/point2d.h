#ifndef POINT2D_H
#define POINT2D_H

#include "logic/include/obj3d/math/point.h"


namespace obj3d {
    class Point2D;
}


class obj3d::Point2D : public obj3d::Point {
public:
    Point2D();

    Point2D(double x, double y);

    double getY() const;

    void setY(double y);

    void changeOrigin(const obj3d::Point2D &origin);

    static double getMaxX(const std::vector<obj3d::Point2D> &points);

    static double getMinX(const std::vector<obj3d::Point2D> &points);

    static double getMaxY(const std::vector<obj3d::Point2D> &points);

    static double getMinY(const std::vector<obj3d::Point2D> &points);

protected:
    double y_;

};


#endif // POINT2D_H
