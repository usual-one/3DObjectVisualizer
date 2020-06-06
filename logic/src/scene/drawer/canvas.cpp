#include "logic/include/scene/drawer/canvas.h"
#include "logic/include/utils/qtdtconverter.h"

Canvas::Canvas() :
    pixmap_(nullptr),
    painter_(nullptr) {
}

Canvas::Canvas(const QSize &size) {
    create(size);
    setAntialiasing();
}

Canvas::~Canvas() {
    clear();
}

QPixmap *Canvas::getPixmap() {
    return pixmap_;
}

void Canvas::update(const QSize &size) {
    clear();
    create(size);
    setAntialiasing();
}

void Canvas::create(const QSize &size) {
    pixmap_ = new QPixmap(size);
    painter_ = new QPainter(pixmap_);
}

void Canvas::clear() {
    if (!isValid()) {
        return;
    }
    painter_->end();
    delete pixmap_;
    delete painter_;
}

void Canvas::setAntialiasing() {
    painter_->setRenderHint(QPainter::Antialiasing);
}

QPainter *Canvas::getPainter() {
    return painter_;
}

size_t Canvas::getWidth() {
    return pixmap_->width();
}

size_t Canvas::getHeight() {
    return pixmap_->height();
}

bool Canvas::isInside(const obj3d::Point2D &pt) {
    return pt.getX() < getWidth() &&
            pt.getX() > 0 &&
            pt.getY() < getHeight() &&
            pt.getY() > 0;
}

bool Canvas::isValid() {
    return pixmap_ != nullptr && painter_ != nullptr;
}

void Canvas::setBackgroundColor(const QColor &color) {
    painter_->fillRect(0, 0, getWidth(), getHeight(), color);
}

void Canvas::setPenColor(const QColor &color) {
    painter_->setPen(color);
    painter_->setBrush(color);
}

void Canvas::drawLine(obj3d::Point2D &begin, obj3d::Point2D &end) {
    if (!isInside(begin) || !isInside(end)) {
        return;
    }
    painter_->drawLine(QtDTConverter::toQPointF(begin),QtDTConverter::toQPointF(end));
}

void Canvas::drawCircle(obj3d::Point2D &center, double radius) {
    const int pie_circle_angle = 5760;
    if (!isInside(obj3d::Point2D(center.getX() - radius, center.getY() - radius)) ||
            !isInside(obj3d::Point2D(center.getX() + radius, center.getY() + radius))) {

    }
    painter_->drawPie(center.getX() - radius, center.getY() - radius,
                      radius * 2, radius * 2,
                      pie_circle_angle, pie_circle_angle);
}
