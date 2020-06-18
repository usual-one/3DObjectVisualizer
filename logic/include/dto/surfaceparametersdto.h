#ifndef SURFACEPARAMETERSDTO_H
#define SURFACEPARAMETERSDTO_H

#include "logic/include/obj3d/surface/surfaceparameters.h"

class SurfaceParametersDTO {
public:
    SurfaceParametersDTO(const obj3d::SurfaceParameters &params);

    obj3d::SurfaceParameters &getParameters();

    void setParameters(const obj3d::SurfaceParameters &params);

private:
    obj3d::SurfaceParameters params_;

};

#endif // SURFACEPARAMETERSDTO_H
