#ifndef TRANSFORMMATRIXBUILDER_H
#define TRANSFORMMATRIXBUILDER_H

#include "logic/include/obj3d/math/matrix.h"

class TransformMatrixBuilder {
public:
    static obj3d::Matrix createMovementMatrix(double x, double y, double z);

    static obj3d::Matrix createMovementMatrix(const obj3d::Vector3D &vec);

    static obj3d::Matrix createRotationMatrix(double x, double y, double z);

    static obj3d::Matrix createRotationMatrix(const obj3d::Vector3D &vec);

    static obj3d::Matrix createScalingMatrix(double x, double y, double z);

    static obj3d::Matrix createScalingMatrix(const obj3d::Vector3D &vec);

private:
    static obj3d::Matrix createRotationOxMatrix(double x);

    static obj3d::Matrix createRotationOyMatrix(double y);

    static obj3d::Matrix createRotatianOzMatrix(double z);
};

#endif // TRANSFORMMATRIXBUILDER_H
