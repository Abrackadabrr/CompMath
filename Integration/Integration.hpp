//
// Created by evgen on 12.10.2022.
//

#ifndef LABS_COMP_MATH_INTEGRATION_HPP
#define LABS_COMP_MATH_INTEGRATION_HPP

#include <complex>
#include <functional>

std::complex<double>
integrate_ossilate(const std::function<double(double)> &g, double frq, double start, double step, int N);

#endif //LABS_COMP_MATH_INTEGRATION_HPP
