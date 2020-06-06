#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

namespace obj3d {
    class Matrix;

    Matrix operator*(const Matrix &self, const Matrix &other);

    class Vector3D;

}

class obj3d::Matrix {
public:
    Matrix();

    Matrix(const std::vector<std::vector<double>> &matr);

    Matrix(const std::vector<double> &vec);

    void addRow(const std::vector<double> &vec);

    void addColumn(const std::vector<double> &vec);

    std::vector<double> getRow(size_t row_num) const;

    std::vector<double> getColumn(size_t col_num) const;

    double calculateDeterminant() const;

    void changeRows(size_t row1_num, size_t row2_num);

    double getElement(size_t row_num, size_t col_num) const;

    size_t getColumnSize() const;

    size_t getRowSize() const;

    bool isSquare() const;

    friend obj3d::Matrix obj3d::operator*(const Matrix &self, const Matrix &other);

    void setElement(size_t row_num, size_t col_num, double value);

    static obj3d::Vector3D solveLinearSystemCramer(const obj3d::Matrix &system,
                                                   const obj3d::Vector3D &result);

    static obj3d::Matrix solveLinearSystemGauss(const obj3d::Matrix &system,
                                                  const obj3d::Matrix &result);

private:
    obj3d::Matrix getMinor(size_t row_num, size_t col_num) const;

    bool isValid(const std::vector<std::vector<double>> &matr);

    std::vector<std::vector<double>> instance_;

};

#endif // MATRIX_H
