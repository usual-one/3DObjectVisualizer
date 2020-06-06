#include <cmath>

#include "config.h"
#include "logic/include/obj3d/math/matrix.h"
#include "logic/include/obj3d/math/exception/matrixexception.h"
#include "logic/include/obj3d/math/vector3d.h"


obj3d::Matrix::Matrix() {
    instance_.clear();
}

obj3d::Matrix::Matrix(const std::vector<std::vector<double> > &matr) {
    if (!isValid(matr)) {
        throw MatrixException(INVALID_MATRIX_MESSAGE);
    }
    instance_ = matr;
}

obj3d::Matrix::Matrix(const std::vector<double> &vec) {
    for (size_t i = 0; i< vec.size(); i++) {
        instance_.push_back({vec[i]});
    }
}

void obj3d::Matrix::addRow(const std::vector<double> &vec) {
    if (getRowSize() && vec.size() != getRowSize()) {
        throw MatrixException(INVALID_VECTOR_MESSAGE);
    }
    instance_.push_back(vec);
}

void obj3d::Matrix::addColumn(const std::vector<double> &vec) {
    if (getColumnSize() && vec.size() != getColumnSize()) {
        throw MatrixException(INVALID_VECTOR_MESSAGE);
    }
    if (!getColumnSize()) {
        for (auto elem : vec) {
            instance_.push_back({elem});
        }
        return;
    }
    for (size_t i = 0; i < vec.size(); i++) {
        instance_[i].push_back(vec[i]);
    }
}

double obj3d::Matrix::calculateDeterminant() const {
    if (!getColumnSize()) {
        throw MatrixException(EMPTY_MATRIX_MESSAGE);
    }
    if (getColumnSize() == 1 && getRowSize() == 1) {
        return instance_[0][0];
    }
    double determinant = 0;
    for (size_t i = 0; i < instance_[0].size(); i++) {
        determinant += pow(-1, i) * getMinor(0, i).calculateDeterminant();
    }
    return determinant;
}

void obj3d::Matrix::changeRows(size_t row1_num, size_t row2_num) {
    std::vector<double> tmp = instance_[row1_num];
    instance_[row1_num] = instance_[row2_num];
    instance_[row2_num] = tmp;
}

std::vector<double> obj3d::Matrix::getRow(size_t row_num) const {
    if (getColumnSize() <= row_num) {
        throw MatrixException(OUT_OF_RANGE_MESSAGE);
    }
    return instance_[row_num];
}

std::vector<double> obj3d::Matrix::getColumn(size_t col_num) const {
    if (getRowSize() <= col_num) {
        throw MatrixException(OUT_OF_RANGE_MESSAGE);
    }
    std::vector<double> column = {};
    for (auto row : instance_) {
        column.push_back(row[col_num]);
    }
    return column;
}

double obj3d::Matrix::getElement(size_t row_num, size_t col_num) const {
    if (getRowSize() <= col_num || getColumnSize() <= row_num) {
        throw MatrixException(OUT_OF_RANGE_MESSAGE);
    }
    return instance_[row_num][col_num];
}

size_t obj3d::Matrix::getColumnSize() const {
    return instance_.size();
}

size_t obj3d::Matrix::getRowSize() const {
    return getColumnSize() ? instance_[0].size() : 0;
}

bool obj3d::Matrix::isSquare() const {
    return getRowSize() == getColumnSize();
}

void obj3d::Matrix::setElement(size_t row_num, size_t col_num, double value) {
    instance_[row_num][col_num] = value;
}

obj3d::Vector3D obj3d::Matrix::solveLinearSystemCramer(const obj3d::Matrix &system,
                                                       const obj3d::Vector3D &result) {
    double main_det = system.calculateDeterminant();
    std::vector<double> result_matr = result.toStdVector();

    if (!main_det) {
        obj3d::Vector3D gauss_result;
        gauss_result.fromMatrix(solveLinearSystemGauss(system, result_matr));
        return gauss_result;
    }

    obj3d::Matrix matr_x;
    matr_x.addColumn(result_matr);
    matr_x.addColumn(system.getColumn(1));
    matr_x.addColumn(system.getColumn(2));
    double new_x = matr_x.calculateDeterminant() / main_det;

    obj3d::Matrix matr_y;
    matr_y.addColumn(system.getColumn(0));
    matr_y.addColumn(result_matr);
    matr_y.addColumn(system.getColumn(2));
    double new_y = matr_y.calculateDeterminant() / main_det;

    obj3d::Matrix matr_z;
    matr_z.addColumn(system.getColumn(0));
    matr_z.addColumn(system.getColumn(1));
    matr_z.addColumn(result_matr);
    double new_z = matr_z.calculateDeterminant() / main_det;

    return obj3d::Vector3D(new_x, new_y, new_z);
}

obj3d::Matrix obj3d::Matrix::solveLinearSystemGauss(const obj3d::Matrix &system,
                                                      const obj3d::Matrix &result) {
    if (!system.isSquare()) {
        throw MatrixException(INVALID_SYSTEM_MESSAGE);
    }
    if (result.getRowSize() != 1) {
        throw MatrixException(INVALID_SYSTEM_MESSAGE);
    }
    if (result.getColumnSize() != system.getColumnSize()) {
        throw MatrixException(INVALID_SYSTEM_MESSAGE);
    }
    obj3d::Matrix system_copy(system);
    obj3d::Matrix result_copy(result);

    obj3d::Matrix result_order = {};
    for (double i = 0 ; i < result.getColumnSize(); i++) {
        result_order.addRow({i});
    }

    for (size_t i = 0; i < system_copy.getRowSize(); i++) {
        if (!system_copy.getElement(i, i)) {
            for (size_t j = i + 1; j < system_copy.getRowSize(); j++) {
                if (system_copy.getElement(j, i)) {
                    system_copy.changeRows(i, j);
                    result_order.changeRows(i, j);
                }
            }
            if (!system_copy.getElement(i, i)) {
                throw MatrixException(INVALID_MATRIX_MESSAGE);
            }
        }
    }

    for (size_t i = 0; i < system_copy.getRowSize() - 1; i++) {
        for (size_t k = i + 1; k < system_copy.getColumnSize(); k++) {
            double subtract_coefficient = system_copy.getElement(k, i) / system_copy.getElement(i, i);
            for (size_t j = 0; j < system_copy.getRowSize(); j++) {
                double system_element = system_copy.getElement(k, j);
                system_element -=  subtract_coefficient * system_copy.getElement(i, j);
                system_copy.setElement(k, j, system_element);
            }
            double result_element = result_copy.getElement(k, 0);
            result_element -= subtract_coefficient * result_copy.getElement(i, 0);
            result_copy.setElement(k, 0, result_element);
        }
    }

    for (size_t i = 0; i < system_copy.getColumnSize(); i++) {
        double divider = system_copy.getElement(i, i);
        for (size_t j = 0; j < system_copy.getRowSize(); j++) {
            system_copy.setElement(i, j, system_copy.getElement(i, j) / divider);
        }
        result_copy.setElement(i, 0, result_copy.getElement(i, 0) / divider);
    }

    for (int i = system_copy.getRowSize() - 1; i > 0; i--) {
        for (int k = i - 1; k > -1; k--) {
            double subtract_coefficient = system_copy.getElement(k, i) / system_copy.getElement(i, i);
            for (size_t j = 0; j < system_copy.getRowSize(); j++) {
                double system_element = system_copy.getElement(k, j);
                system_element -=  subtract_coefficient * system_copy.getElement(i, j);
                system_copy.setElement(k, j, system_element);
            }
            double result_element = result_copy.getElement(k, 0);
            result_element -= subtract_coefficient * result_copy.getElement(i, 0);
            result_copy.setElement(k, 0, result_element);
        }
    }

    for (size_t i = 0; i < result_order.getColumnSize(); i++) {
        result_copy.changeRows(i, result_order.getElement(i, 0));
        result_order.changeRows(i, result_order.getElement(i, 0));
    }

    return result_copy;
}

obj3d::Matrix obj3d::Matrix::getMinor(size_t row_num, size_t col_num) const {
    obj3d::Matrix minor;
    for (size_t i = 0; i < getColumnSize(); i++) {
        if (i == row_num) {
            continue;
        }
        std::vector<double> row = {};
        for (size_t j = 0; j < getRowSize(); j++) {
            if (j == col_num) {
                continue;
            }
            row.push_back(getElement(i, j));
        }
        minor.addRow(row);
    }
    return minor;
}

obj3d::Matrix obj3d::operator*(const obj3d::Matrix &self, const obj3d::Matrix &other) {
    if (self.getRowSize() != other.getColumnSize()) {
        throw MatrixException(INVALID_MATRIX_MESSAGE);
    }
    std::vector<std::vector<double>> product;
    for (size_t i = 0; i < self.getColumnSize(); i++) {
        product.push_back({});
        for (size_t j = 0; j < other.getRowSize(); j++) {
            double element = 0;
            for (size_t k = 0; k < other.getColumnSize(); k++) {
                element += self.getElement(i, k) * other.getElement(k, j);
            }
            product[i].push_back(element);
        }
    }
    return obj3d::Matrix(product);
}

bool obj3d::Matrix::isValid(const std::vector<std::vector<double> > &matr) {
    size_t row_size = matr[0].size();
    for (auto row : matr) {
        if (row.size() != row_size) {
            return false;
        }
    }
    return true;
}
