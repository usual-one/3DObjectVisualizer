#include <cmath>

#include "logic/include/obj3d/math/vector3d.h"


obj3d::Vector3D::Vector3D() :
    obj3d::Point3D() {}

obj3d::Vector3D::Vector3D(double x, double y, double z) :
    obj3d::Point3D(x, y, z) {}

obj3d::Vector3D::Vector3D(const obj3d::Point3D &pt) :
    obj3d::Point3D(pt) {}

obj3d::Vector3D::Vector3D(const obj3d::Point3D &p1, const obj3d::Point3D &p2) :
    obj3d::Point3D(p2.getX() - p1.getX(),
                   p2.getY() - p1.getY(),
                   p2.getZ() - p1.getZ()) {}

void obj3d::Vector3D::transform(const obj3d::Matrix &transform_matr) {
    obj3d::Matrix product = transform_matr * toHomogeneousMatrix();
    fromMatrix(product);
}

std::vector<double> obj3d::Vector3D::toStdVector() const {
    return std::vector({x_, y_, z_});
}

obj3d::Matrix obj3d::Vector3D::toMatrix() {
    obj3d::Matrix matr;
    matr.addColumn(toStdVector());
    return matr;
}

double obj3d::Vector3D::size() {
    return sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2));
}

void obj3d::Vector3D::changeSize(double new_size) {
    double old_size = size();
    x_ *= (new_size / old_size);
    y_ *= (new_size / old_size);
    z_ *= (new_size / old_size);
}

bool obj3d::Vector3D::areCoplanar(const obj3d::Vector3D &vec1,
                                  const obj3d::Vector3D &vec2,
                                  const obj3d::Vector3D &vec3) {
    obj3d::Matrix transform_matr;
    transform_matr.addColumn(vec1.toStdVector());
    transform_matr.addColumn(vec2.toStdVector());
    transform_matr.addColumn(vec3.toStdVector());
    return transform_matr.calculateDeterminant() == 0;
}

obj3d::Vector3D obj3d::Vector3D::operator*(const obj3d::Vector3D &other) {
    return vectorProduct(other);
}

obj3d::Matrix obj3d::Vector3D::toHomogeneousMatrix() {
    obj3d::Matrix matr = toMatrix();
    matr.addRow({1});
    return matr;
}

obj3d::Vector3D obj3d::Vector3D::vectorProduct(const obj3d::Vector3D &vec) {
    obj3d::Matrix i_matr;
    i_matr.addRow({y_, z_});
    i_matr.addRow({vec.getY(), vec.getZ()});

    obj3d::Matrix j_matr;
    j_matr.addRow({x_, z_});
    j_matr.addRow({vec.getX(), vec.getZ()});

    obj3d::Matrix k_matr;
    k_matr.addRow({x_, y_});
    k_matr.addRow({vec.getX(), vec.getY()});

    return obj3d::Vector3D(i_matr.calculateDeterminant(),
                           -j_matr.calculateDeterminant(),
                           k_matr.calculateDeterminant());
}

void obj3d::Vector3D::fromMatrix(const obj3d::Matrix &matr) {
    x_ = matr.getElement(0, 0);
    y_ = matr.getElement(1, 0);
    z_ = matr.getElement(2, 0);
}
