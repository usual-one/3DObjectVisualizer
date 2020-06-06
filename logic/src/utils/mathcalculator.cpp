#include <cmath>

#include "logic/include/utils/mathcalculator.h"

#define DEGREES_IN_PI 180
#define _USE_MATH_DEFINES

double MathCalculator::toRadians(double degrees) {
    return degrees * (M_PI / DEGREES_IN_PI);
}
