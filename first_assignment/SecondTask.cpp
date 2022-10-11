//
// Created by evgen on 11.10.2022.
//

#include <complex>
#include <cmath>
#include <iostream>

#include "Integration/Integration.hpp"

double g(double x) {
    return std::exp(-x * x) * std::cos(2 * x);
}

int main() {
    std::complex<double> i = {0., 1.};
    double freq = 100;
    double start = 0;
    double stop = 3;
    int N = 30000;
    double step = (stop - start) / N;
    double res = integrate_ossilate(g, freq, start, step, N).imag();
    std::cout.precision(20);
    std::cout << res << std::endl;
}
