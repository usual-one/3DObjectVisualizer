#include "logic/include/dto/surfaceparametersdto.h"

SurfaceParametersDTO::SurfaceParametersDTO(const obj3d::SurfaceParameters &params) :
    params_(params) {}

obj3d::SurfaceParameters &SurfaceParametersDTO::getParameters() {
    return params_;
}

void SurfaceParametersDTO::setParameters(const obj3d::SurfaceParameters &params) {
    params_ = params;
}
