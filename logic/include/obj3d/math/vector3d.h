#ifndef VECTOR_H
#define VECTOR_H

#include "logic/include/obj3d/math/point3d.h"
#include "logic/include/obj3d/math/matrix.h"


namespace obj3d {
    class Vector3D;

    class Basis3D;
}


class obj3d::Vector3D : public obj3d::Point3D {
public:
    Vector3D();

    Vector3D(double x, double y, double z);

    Vector3D(const obj3d::Point3D &pt);

    Vector3D(const obj3d::Point3D &p1, const obj3d::Point3D &p2);

    void fromMatrix(const obj3d::Matrix &matr);

    void transform(const obj3d::Matrix &transform_matr);

    std::vector<double> toStdVector() const;

    obj3d::Matrix toMatrix();

    double size();

    void changeSize(double new_size);

    static bool areCoplanar(const obj3d::Vector3D &vec1,
                            const obj3d::Vector3D &vec2,
                            const obj3d::Vector3D &vec3);

    obj3d::Vector3D operator*(const obj3d::Vector3D &other);

private:
    obj3d::Matrix toHomogeneousMatrix();

    obj3d::Vector3D vectorProduct(const obj3d::Vector3D &vec);

};

#endif // VECTOR_H
