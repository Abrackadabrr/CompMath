//
// Created by evgen on 13.10.2022.
//

#include "CompMath/Interpolation/NewtonInterpolation.hpp"
#include "CompMath/Interpolation/SplineInterpolator.h"
#include <array>
#include <iostream>

int main() {
    std::array<double, 10> years = {1.910, 1.920, 1.930, 1.940, 1.950, 1.960, 1.970, 1.980, 1.990, 2.000};
    const double h = 0.01;
    std::array<double, 10> population = {
            0.92228496, 1.06021537, 1.23202624, 1.32164569, 1.51325798, 1.79323175, 2.03211926, 2.26545805, 2.48709873,
            2.81421906};
    const double xP = 2.010;
    const auto NeIn = NewtonInterpolation<double, double, 10>(years, population);
    const auto SpIn = CubicSplineInterpolator<10>(years, population);
    const double populationXNeIn = NeIn.interpolate(xP);
    const double populationXSpIn = SpIn.extrapolate(xP);
    std::cout.precision(20);
    std::cout << "Знач1
