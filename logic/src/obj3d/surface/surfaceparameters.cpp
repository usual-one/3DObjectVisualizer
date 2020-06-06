#include "logic/include/obj3d/surface/surfaceparameters.h"

obj3d::SurfaceParameters::SurfaceParameters() {
    normalization_needed_ = false;
    min_z_ = 0;
    max_z_ = 0;
    x_step_ = 0;
    y_step_ = 0;
}

bool obj3d::SurfaceParameters::isNormalizationNeeded() {
    return normalization_needed_;
}

double obj3d::SurfaceParameters::getMin() {
    return min_z_;
}

double obj3d::SurfaceParameters::getMax() {
    return max_z_;
}

double obj3d::SurfaceParameters::getXStep() {
    return x_step_;
}

double obj3d::SurfaceParameters::getYStep() {
    return y_step_;
}

void obj3d::SurfaceParameters::setNormalizationNeeded(bool normalization_needed) {
    normalization_needed_ = normalization_needed;
}

void obj3d::SurfaceParameters::setMin(double min_z) {
    min_z_ = min_z;
}

void obj3d::SurfaceParameters::setMax(double max_z) {
    max_z_ = max_z;
}

void obj3d::SurfaceParameters::setXStep(double x_step) {
    x_step_ = x_step;
}

void obj3d::SurfaceParameters::setYStep(double y_step) {
    y_step_ = y_step;
}
