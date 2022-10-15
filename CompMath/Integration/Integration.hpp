//
// Created by evgen on 12.10.2022.
//

#ifndef LABS_COMP_MATH_INTEGRATION_HPP
#define LABS_COMP_MATH_INTEGRATION_HPP

#include <complex>
#include <functional>

template<typename Type>
std::complex<Type>
integrate_ossilate(const std::function<Type(Type)> &g, Type frq, Type start, Type step, int N) {
    std::complex<Type> res = {0, 0};
    std::complex<Type> mni{0, 1};
    std::complex<Type> one{1, 0};
    for (int i = 0; i < N; i++) {
        const Type x_i = start + i * step;
        const Type g_12 = g(x_i + step / 2);
        const std::complex<Type> mul1 = 1. / (mni * frq);
        const std::complex<Type> mul2 = std::exp(mni * frq * x_i);
        const std::complex<Type> mul3 = (std::exp(mni * frq * step) - one);
        res += g_12 * mul1 * mul2 * mul3;
    }
    return res;
};

#endif //LABS_COMP_MATH_INTEGRATION_HPP
