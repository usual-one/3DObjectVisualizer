#ifndef SURFACEVALUESDTO_H
#define SURFACEVALUESDTO_H

#include <vector>

class SurfaceValuesDTO {
public:
    SurfaceValuesDTO(const std::vector<std::vector<double>> &values);

    const std::vector<std::vector<double>> &getValues() const;

    void setValues(const std::vector<std::vector<double>> &values);

private:
    std::vector<std::vector<double>> values_;

};

#endif // SURFACEVALUESDTO_H
