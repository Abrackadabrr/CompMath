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
    std::cout << "Значения в точке 2010: Ньютон = " << populationXNeIn * 1e8 <<", Кубический сплайн = " << populationXSpIn * 1e8 << std::endl;

    // оценка погрешности экстраполяции
//    std::array<double, 11> y{};
//    std::array<double, 11> x{};
//    y[10] = populationX;
//    x[10] = xP;
//    for (int i = 0; i< 10; i++) {x[i] = years[i]; y[i] = population[i];}
//    auto interp = NewtonInterpolation<double, double, 11>(x, y);
//
//    const double error = std::pow(h, 9) ;
//    std::cout << "Ошибка в точке 2010: " << error << std::endl;
}
