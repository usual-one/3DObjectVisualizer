#include <cmath>

#include "logic/include/obj3d/math/transformmatrixbuilder.h"

obj3d::Matrix TransformMatrixBuilder::createRotationMatrix(double x, double y, double z) {
    return createRotationOxMatrix(x) * createRotationOyMatrix(y) * createRotatianOzMatrix(z);
}

obj3d::Matrix TransformMatrixBuilder::createMovementMatrix(double x, double y, double z) {
    std::vector<std::vector<double>> matr = {};
    matr.push_back({1, 0, 0, x});
    matr.push_back({0, 1, 0, y});
    matr.push_back({0, 0, 1, z});
    matr.push_back({0, 0, 0, 1});
    return obj3d::Matrix(matr);
}

obj3d::Matrix TransformMatrixBuilder::createScalingMatrix(double x, double y, double z) {
    std::vector<std::vector<double>> matr = {};
    matr.push_back({x, 0, 0, 0});
    matr.push_back({0, y, 0, 0});
    matr.push_back({0, 0, z, 0});
    matr.push_back({0, 0, 0, 1});
    return obj3d::Matrix(matr);
}

obj3d::Matrix TransformMatrixBuilder::createRotationOxMatrix(double x) {
    std::vector<std::vector<double>> matr = {};
    matr.push_back({1, 0, 0, 0});
    matr.push_back({0, cos(x), -sin(x), 0});
    matr.push_back({0, sin(x), cos(x), 0});
    matr.push_back({0, 0, 0, 1});
    return obj3d::Matrix(matr);
}

obj3d::Matrix TransformMatrixBuilder::createRotationOyMatrix(double y) {
    std::vector<std::vector<double>> matr = {};
    matr.push_back({cos(y), 0, sin(y), 0});
    matr.push_back({0, 1, 0, 0});
    matr.push_back({-sin(y), 0, cos(y), 0});
    matr.push_back({0, 0, 0, 1});
    return obj3d::Matrix(matr);
}

obj3d::Matrix TransformMatrixBuilder::createRotatianOzMatrix(double z) {
    std::vector<std::vector<double>> matr = {};
    matr.push_back({cos(z), -sin(z), 0, 0});
    matr.push_back({sin(z), cos(z), 0, 0});
    matr.push_back({0, 0, 1, 0});
    matr.push_back({0, 0, 0, 1});
    return obj3d::Matrix(matr);
}
