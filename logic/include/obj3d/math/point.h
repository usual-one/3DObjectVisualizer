#ifndef POINT_H
#define POINT_H

#include <vector>

namespace obj3d {
    class Point;
}


class obj3d::Point {
public:
    Point();

    Point(double x);

    double getX() const;

    void setX(double x);

protected:
    double x_;

};


#endif // POINT_H
