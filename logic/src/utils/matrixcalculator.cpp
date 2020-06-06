#include <algorithm>
#include <cmath>

#include "logic/include/utils/matrixcalculator.h"
#include "logic/include/utils/exception/matrixcalculatorexception.h"
#include "config.h"

double MatrixCalculator::getMinimum(const std::vector<std::vector<double>> &matr) {
    std::vector<double> vec = toVector(matr);
    return  *std::min_element(vec.begin(), vec.end());
}

double MatrixCalculator::getMaximum(const std::vector<std::vector<double>> &matr) {
    std::vector<double> vec = toVector(matr);
    return  *std::max_element(vec.begin(), vec.end());
}

std::pair<double, double>
MatrixCalculator::getMaxDiffNeighbourValues(const std::vector<std::vector<double>> &matr) {
    if (!matr.size() || toVector(matr).size() == 1) {
        throw MatrixCalculatorException(EMPTY_MATRIX_MESSAGE);
    }

    std::pair<double, double> neighbour_values;
    double max_diff = 0;

    for (size_t i = 0; i < matr.size(); i++) {
        for (size_t j = 0; j < matr[i].size(); j++) {
            std::vector<double> comparable_values = {};
            if (j > 0) {
                comparable_values.push_back(matr[i][j - 1]);
            }
            if (j < matr[i].size() - 1) {
                comparable_values.push_back(matr[i][j + 1]);
            }
            if (i > 0 && matr[i - 1].size() > j) {
                comparable_values.push_back(matr[i - 1][j]);
            }
            if (i < matr.size() - 1 && matr[i + 1].size() > j) {
                comparable_values.push_back(matr[i + 1][j]);
            }
            for (size_t k = 0; k < comparable_values.size(); k++) {
                if (max_diff <= fabs(matr[i][j] - comparable_values[k])) {
                    max_diff = fabs(matr[i][j] - comparable_values[k]);
                    neighbour_values = {matr[i][j], comparable_values[k]};
                }
            }
        }
    }

    return neighbour_values;
}

std::vector<double> MatrixCalculator::toVector(const std::vector<std::vector<double>> &matr) {
    std::vector<double> vec = {};
    for (size_t i = 0; i < matr.size(); i++) {
        vec.insert(vec.end(), matr[i].begin(), matr[i].end());
    }
    return vec;
}
