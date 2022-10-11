//
// Created by evgen on 27.09.2022.
//

#include <iostream>
#include "Interpolation/NewtonInterpolation.hpp"
#include "Interpolation/SplineInterpolator.h"

int main() {
    constexpr int N = 11;
    constexpr double x_0 = 0.95;
    std::array<double, N> f{0, 0.033, 0.067, 0.100, 0.134, 0.168, 0.203, 0.238, 0.273, 0.309, 0.346};
    std::array<double, N> x{0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};

    NewtonInterpolation<double, double, N> interpolator(x, f);
    double f_x_0 = interpolator.interpolate(x_0);
    std::cout << "Значение в 0.95, полученное методом Ньютона: "<< f_x_0 << std::endl << "Ошибка: "
    << interpolator.interpError(0.95, 15) << std::endl;
    CubicSplineInterpolator<N> interpolator2(x, f);
    f_x_0 = interpolator2.interpolate(x_0);
    std::cout << "Значение в 0.95, полученное с помощью сплайна: "<< f_x_0 << std::endl << "Ошибка: "
    << interpolator2.interpErrorUniformGrid(0.95, 0.1, 0.1) << std::endl;
}
