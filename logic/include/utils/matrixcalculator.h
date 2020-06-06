#ifndef MATRIXCALCULATOR_H
#define MATRIXCALCULATOR_H

#include <vector>

class MatrixCalculator {
public:
    static double getMinimum(const std::vector<std::vector<double>> &matr);

    static double getMaximum(const std::vector<std::vector<double>> &matr);

    static std::pair<double, double> getMaxDiffNeighbourValues(const std::vector<std::vector<double>> &matr);

private:
    static std::vector<double> toVector(const std::vector<std::vector<double>> &matr);

};

#endif // MATRIXCALCULATOR_H
