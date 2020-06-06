#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <memory>

#include "logic/include/obj3d/math/point2d.h"


namespace obj3d {
    class Rectangle2D;
}


class obj3d::Rectangle2D {
public:
    Rectangle2D();

    Rectangle2D(const obj3d::Point2D &lb, const obj3d::Point2D &lt,
                const obj3d::Point2D &rb, const obj3d::Point2D &rt);

    std::shared_ptr<obj3d::Point2D> getLeftBottom();

    std::shared_ptr<obj3d::Point2D> getLeftTop();

    std::shared_ptr<obj3d::Point2D> getRightBottom();

    std::shared_ptr<obj3d::Point2D> getRightTop();

    bool isInside(const obj3d::Point2D &point) const;

    void changeOrigin(const obj3d::Point2D &origin);

private:
    std::shared_ptr<obj3d::Point2D> left_bottom_;

    std::shared_ptr<obj3d::Point2D> left_top_;

    std::shared_ptr<obj3d::Point2D> right_bottom_;

    std::shared_ptr<obj3d::Point2D> right_top_;

};


#endif // RECTANGLE_H
