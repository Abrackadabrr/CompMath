//
// Created by evgen on 19.10.2022.
//

#include "CompMath/Interpolation/NewtonInterpolation.hpp"
#include <iostream>

int main() {
    std::array<double, 3> x = getChebyshevNodes<double, 3>(2, 5);
    std::array<double, 3> f = {-1.76, -13.681, -50.639};
    NewtonInterpolation<double, double, 3> interp(x, f);
    std::cout << interp.interpolate(3.) << std::endl;
}