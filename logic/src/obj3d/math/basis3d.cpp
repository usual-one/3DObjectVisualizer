#include "config.h"
#include "logic/include/obj3d/math/basis3d.h"
#include "logic/include/obj3d/math/exception/basisexception.h"


obj3d::Basis3D::Basis3D(obj3d::Vector3D i, obj3d::Vector3D j, obj3d::Vector3D k) {
    if (obj3d::Vector3D::areCoplanar(i, j, k)) {
        throw BasisException(NOT_BASIS_MESSAGE);
    }
    i_ = std::make_shared<obj3d::Vector3D>(i);
    j_ = std::make_shared<obj3d::Vector3D>(j);
    k_ = std::make_shared<obj3d::Vector3D>(k);
    changeSizeToDefault();
}

std::shared_ptr<obj3d::Vector3D> obj3d::Basis3D::getI() {
    return i_;
}

std::shared_ptr<obj3d::Vector3D> obj3d::Basis3D::getJ() {
    return j_;
}

std::shared_ptr<obj3d::Vector3D> obj3d::Basis3D::getK() {
    return k_;
}

obj3d::Vector3D obj3d::Basis3D::expandVector(const obj3d::Vector3D &vec) {
    obj3d::Matrix main_matr;
    main_matr.addColumn(i_->toStdVector());
    main_matr.addColumn(j_->toStdVector());
    main_matr.addColumn(k_->toStdVector());
    return obj3d::Matrix::solveLinearSystemCramer(main_matr, vec);
}

void obj3d::Basis3D::changeSizeToDefault() {
    i_->changeSize(1);
    j_->changeSize(1);
    k_->changeSize(1);
}
