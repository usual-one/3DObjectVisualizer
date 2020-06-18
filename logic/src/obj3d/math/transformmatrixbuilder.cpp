#include <cmath>

#include "logic/include/obj3d/math/transformmatrixbuilder.h"
#include "logic/include/utils/mathcalculator.h"
#include "logic/include/obj3d/math/vector3d.h"

obj3d::Matrix TransformMatrixBuilder::createRotationMatrix(double x, double y, double z) {
    return createRotationOxMatrix(x) * createRotationOyMatrix(y) * createRotatianOzMatrix(z);
}

obj3d::Matrix TransformMatrixBuilder::createRotationMatrix(const obj3d::Vector3D &vec) {
    return createRotationMatrix(vec.getX(), vec.getY(), vec.getZ());
}

obj3d::Matrix TransformMatrixBuilder::createMovementMatrix(double x, double y, double z) {
    std::vector<std::vector<double>> matr = {};
    matr.push_back({1, 0, 0, x});
    matr.push_back({0, 1, 0, y});
    matr.push_back({0, 0, 1, z});
    matr.push_back({0, 0, 0, 1});
    return obj3d::Matrix(matr);
}

obj3d::Matrix TransformMatrixBuilder::createMovementMatrix(const obj3d::Vector3D &vec) {
    return createMovementMatrix(vec.getX(), vec.getY(), vec.getZ());
}

obj3d::Matrix TransformMatrixBuilder::createScalingMatrix(double x, double y, double z) {
    std::vector<std::vector<double>> matr = {};
    matr.push_back({x, 0, 0, 0});
    matr.push_back({0, y, 0, 0});
    matr.push_back({0, 0, z, 0});
    matr.push_back({0, 0, 0, 1});
    return obj3d::Matrix(matr);
}

obj3d::Matrix TransformMatrixBuilder::createScalingMatrix(const obj3d::Vector3D &vec) {
    return createScalingMatrix(vec.getX(), vec.getY(), vec.getZ());
}

obj3d::Matrix TransformMatrixBuilder::createRotationOxMatrix(double degrees) {
    std::vector<std::vector<double>> matr = {};
    matr.push_back({1, 0, 0, 0});
    matr.push_back({0, cos(MathCalculator::toRadians(degrees)), -sin(MathCalculator::toRadians(degrees)), 0});
    matr.push_back({0, sin(MathCalculator::toRadians(degrees)), cos(MathCalculator::toRadians(degrees)), 0});
    matr.push_back({0, 0, 0, 1});
    return obj3d::Matrix(matr);
}

obj3d::Matrix TransformMatrixBuilder::createRotationOyMatrix(double degrees) {
    std::vector<std::vector<double>> matr = {};
    matr.push_back({cos(MathCalculator::toRadians(degrees)), 0, sin(MathCalculator::toRadians(degrees)), 0});
    matr.push_back({0, 1, 0, 0});
    matr.push_back({-sin(MathCalculator::toRadians(degrees)), 0, cos(MathCalculator::toRadians(degrees)), 0});
    matr.push_back({0, 0, 0, 1});
    return obj3d::Matrix(matr);
}

obj3d::Matrix TransformMatrixBuilder::createRotatianOzMatrix(double degrees) {
    std::vector<std::vector<double>> matr = {};
    matr.push_back({cos(MathCalculator::toRadians(degrees)), -sin(MathCalculator::toRadians(degrees)), 0, 0});
    matr.push_back({sin(MathCalculator::toRadians(degrees)), cos(MathCalculator::toRadians(degrees)), 0, 0});
    matr.push_back({0, 0, 1, 0});
    matr.push_back({0, 0, 0, 1});
    return obj3d::Matrix(matr);
}
