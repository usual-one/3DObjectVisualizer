#ifndef SURFACEPARAMETERS_H
#define SURFACEPARAMETERS_H

namespace obj3d {
    class SurfaceParameters;
}

class obj3d::SurfaceParameters {
public:
    SurfaceParameters();

    bool isNormalizationNeeded();

    double getMin();

    double getMax();

    double getXStep();

    double getYStep();

    void setNormalizationNeeded(bool normalization_needed);

    void setMin(double min_z);

    void setMax(double max_z);

    void setXStep(double x_step);

    void setYStep(double y_step);

private:
    bool normalization_needed_;

    double min_z_;

    double max_z_;

    double x_step_;

    double y_step_;

};

#endif // SURFACEPARAMETERS_H
