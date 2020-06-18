#include "logic/include/dto/surfacevaluesdto.h"

SurfaceValuesDTO::SurfaceValuesDTO(const std::vector<std::vector<double>> &values) :
    values_(values) {}

const std::vector<std::vector<double>> &SurfaceValuesDTO::getValues() const {
    return values_;
}

void SurfaceValuesDTO::setValues(const std::vector<std::vector<double>> &values) {
    values_ = values;
}
