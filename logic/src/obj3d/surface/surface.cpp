#include <cmath>

#include "logic/include/obj3d/surface/surface.h"
#include "logic/include/utils/matrixcalculator.h"
#include "logic/include/utils/mathcalculator.h"
#include "config.h"

size_t obj3d::Surface::count_ = 0;

obj3d::Surface::Surface(const std::vector<std::vector<double>> &values) {
    count_++;
    tag_ = std::make_shared<std::string>(DEFAULT_SURFACE_TAG + std::to_string(count_));
    values_ = values;
    params_ = calculateParameters();
}

std::set<std::shared_ptr<obj3d::Vertex3D>> obj3d::Surface::toVertices() const {
    std::vector<std::vector<std::shared_ptr<obj3d::Vertex3D>>> vertices_matr = {};
    std::vector<std::vector<obj3d::Point3D>> points = toPoints3D();

    for (size_t i = 0; i < points.size(); i++) {
        vertices_matr.push_back({});
        for (size_t j = 0; j < points[i].size(); j++) {
            vertices_matr[i].push_back(std::make_shared<obj3d::Vertex3D>(points[i][j],
                                                                         i * points[0].size() + j));
        }
    }

    setConnections(vertices_matr);

    std::set<std::shared_ptr<obj3d::Vertex3D>> vertices_set = {};
    for (auto row : vertices_matr) {
        vertices_set.insert(row.begin(), row.end());
    }

    return vertices_set;
}

std::shared_ptr<obj3d::SurfaceParameters> obj3d::Surface::getParameters() {
    return params_;
}

void obj3d::Surface::setParameters(std::shared_ptr<obj3d::SurfaceParameters> params) {
    params_ = params;
}

std::vector<std::vector<double>> &obj3d::Surface::getValues() {
    return values_;
}

std::shared_ptr<obj3d::SurfaceParameters> obj3d::Surface::calculateParameters() const {
    std::shared_ptr<SurfaceParameters> params = std::make_shared<SurfaceParameters>();

    std::pair<double, double> max_diff_points = MatrixCalculator::getMaxDiffNeighbourValues(values_);
    double default_step = fabs(max_diff_points.first - max_diff_points.second) /
            tan(MathCalculator::toRadians(DEFAULT_MAX_NEIGHBOUR_ANGLE));
    params->setXStep(default_step);
    params->setYStep(default_step);

    return params;
}

std::vector<std::vector<double>> obj3d::Surface::normalizeValues() const {
    if (!params_->isNormalizationNeeded()) {
        return values_;
    }
    std::vector<std::vector<double>> normalized_values = {};

    double min = MatrixCalculator::getMinimum(values_);
    double max = MatrixCalculator::getMaximum(values_);

    double normalized_value = (params_->getMax() - params_->getMin()) / 2;

    for (size_t i = 0; i < values_.size(); i++) {
        normalized_values.push_back({});
        for (size_t j = 0; j < values_[i].size(); j++) {
            if (max - min) {
                 normalized_value = params_->getMin() +
                         ((values_[i][j] - min) * (params_->getMax() - params_->getMin())) / (max - min);
            }
            normalized_values[i].push_back(normalized_value);
        }
    }
    return normalized_values;
}

std::vector<std::vector<obj3d::Point3D>> obj3d::Surface::toPoints3D() const {
    std::vector<std::vector<double>> normalized_values = normalizeValues();
    std::vector<std::vector<obj3d::Point3D>> points = {};

    for (size_t i = 0; i < normalized_values.size(); i++) {
        points.push_back({});
        for (size_t j = 0; j < normalized_values[i].size(); j++) {
            double x_value = j * params_->getXStep();
            double y_value = i * params_->getYStep();
            points[i].push_back(Point3D(x_value, y_value, normalized_values[i][j]));
        }
    }

    return points;
}

void obj3d::Surface::setConnections(std::vector<std::vector<std::shared_ptr<obj3d::Vertex3D>>> &vertices) const {
    for (size_t i = 0; i < vertices.size(); i++) {
        for (size_t j = 0; j < vertices[i].size(); j++) {
            if (j > 0) {
                vertices[i][j]->addConnection(vertices[i][j - 1]);
            }
            if (j < vertices[i].size() - 1) {
                vertices[i][j]->addConnection(vertices[i][j + 1]);
            }
            if (i > 0 && vertices[i - 1].size() > j) {
                vertices[i][j]->addConnection(vertices[i - 1][j]);
            }
            if (i < vertices.size() - 1 && vertices[i + 1].size() > j) {
                vertices[i][j]->addConnection(vertices[i + 1][j]);
            }
        }
    }
}
