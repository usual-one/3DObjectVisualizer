#include "logic/include/obj3d/math/rectangle2d.h"


obj3d::Rectangle2D::Rectangle2D() :
    left_bottom_(std::make_shared<obj3d::Point2D>()),
    left_top_(std::make_shared<obj3d::Point2D>()),
    right_bottom_(std::make_shared<obj3d::Point2D>()),
    right_top_(std::make_shared<obj3d::Point2D>()) {}

obj3d::Rectangle2D::Rectangle2D(const obj3d::Point2D &lb, const obj3d::Point2D &lt,
                                const obj3d::Point2D &rb, const obj3d::Point2D &rt) :
    left_bottom_(std::make_shared<obj3d::Point2D>(lb)),
    left_top_(std::make_shared<obj3d::Point2D>(lt)),
    right_bottom_(std::make_shared<obj3d::Point2D>(rb)),
    right_top_(std::make_shared<obj3d::Point2D>(rt)) {}

std::shared_ptr<obj3d::Point2D> obj3d::Rectangle2D::getLeftBottom() {
    return left_bottom_;
}

std::shared_ptr<obj3d::Point2D> obj3d::Rectangle2D::getLeftTop() {
    return left_top_;
}

std::shared_ptr<obj3d::Point2D> obj3d::Rectangle2D::getRightBottom() {
    return right_bottom_;
}

std::shared_ptr<obj3d::Point2D> obj3d::Rectangle2D::getRightTop() {
    return right_top_;
}

bool obj3d::Rectangle2D::isInside(const obj3d::Point2D &point) const{
    return point.getX() >= left_bottom_->getX() &&
            point.getX() <= right_bottom_->getX() &&
            point.getY() >= left_bottom_->getY() &&
            point.getY() <= left_top_->getY();
}

void obj3d::Rectangle2D::changeOrigin(const obj3d::Point2D &origin) {
    left_bottom_->changeOrigin(origin);
    left_top_->changeOrigin(origin);
    right_bottom_->changeOrigin(origin);
    right_top_->changeOrigin(origin);
}
