//
// Created by evgen on 12.10.2022.
//

#include "Integration.hpp"

std::complex<double>
integrate_ossilate(const std::function<double(double)> &g, double frq, double start, double step, int N) {
    std::complex<double> res = {0, 0};
    std::complex<double> mni{0, 1};
    std::complex<double> one{1, 0};
    for (int i = 0; i < N; i++) {
        const double x_i = start + i * step;
        const double g_12 = g(x_i + step / 2);
        const std::complex<double> mul1 = 1. / (mni * frq);
        const std::complex<double> mul2 = std::exp(mni * frq * x_i);
        const std::complex<double> mul3 = (std::exp(mni * frq * step) - one);
        res += g_12 * mul1 * mul2 * mul3;
    }
    return res;
};