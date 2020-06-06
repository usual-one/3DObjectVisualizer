#ifndef BASIS_H
#define BASIS_H

#include <memory>

#include "logic/include/obj3d/math/vector3d.h"


namespace obj3d {
    class Basis3D;
}


class obj3d::Basis3D {
public:
    Basis3D();

    Basis3D(obj3d::Vector3D i, obj3d::Vector3D j, obj3d::Vector3D k);

    std::shared_ptr<obj3d::Vector3D> getI();

    std::shared_ptr<obj3d::Vector3D> getJ();

    std::shared_ptr<obj3d::Vector3D> getK();

    obj3d::Vector3D expandVector(const obj3d::Vector3D &vec);

private:
    void changeSizeToDefault();

    std::shared_ptr<obj3d::Vector3D> i_;

    std::shared_ptr<obj3d::Vector3D> j_;

    std::shared_ptr<obj3d::Vector3D> k_;

};


#endif // BASIS_H
