//
// Created by evgen on 19.08.2022.
//

#ifndef NEWTONINTERPOLATION_HPP_
#define NEWTONINTERPOLATION_HPP_

#include <array>
#include <cmath>

int fact(int n){
    return (n==0) || (n==1) ? 1 : n* fact(n-1);
}

using indexType = int;

/***
 * Интерполтор Ньютона
 * @tparam realType - тип значений аргумента
 * @tparam valueType - тип значений функции
 * @tparam N - количество точек
 */
template <typename realType, typename valueType, indexType N>
class NewtonInterpolation {
    static_assert(N >= 2);

private:
    std::array<valueType, N> dividedDifferences_;
    std::array<realType, N> xData_;

public:
    NewtonInterpolation(const std::array<realType, N>& xData, const std::array<valueType, N>& yData);
    valueType interpolate(const realType& x) const noexcept;
    valueType interpError(const realType& x, const valueType& max_proizvodnaya);
    const std::array<valueType, N>& getDiff();
};

template <typename realType, typename valueType, indexType N>
NewtonInterpolation<realType, valueType, N>::NewtonInterpolation(const std::array<realType, N>& xData,
                                                                 const std::array<valueType, N>& yData)
        : dividedDifferences_(yData), xData_(xData) {
    using delta = decltype(xData[0] - xData[1]);

    indexType order = 1;
    while (order < N) {
        indexType last = N - order;
        valueType tmp = dividedDifferences_[0];
        for (indexType i = 0; i < last; i++) {
            delta znam = xData[i + order] - xData[i];
            valueType chisl = dividedDifferences_[i + 1] - dividedDifferences_[i];
            dividedDifferences_[i] = chisl / znam;
        }
        dividedDifferences_[last] = tmp;
        order++;
    }
}

template <typename realType, typename valueType, indexType N>
valueType NewtonInterpolation<realType, valueType, N>::interpolate(
        const realType& x) const noexcept {

    using delta = decltype(xData_[0] - xData_[1]);

    auto argumentDifference = static_cast<delta>(1);
    valueType result = dividedDifferences_[N - 1];  // f(x_0)
    for (int i = 0; i < N - 1; i++) {
        argumentDifference *= (x - xData_[i]);
        result += (dividedDifferences_[N - i - 2] * argumentDifference);
    }
    return result;
}

template <typename realType, typename valueType, indexType N>
valueType NewtonInterpolation<realType, valueType, N>::interpError(const realType& x, const valueType& max_proizvodnaya) {
    const int nfac = fact(N);
    realType mult = 1;
    for (auto i: xData_) mult *= (x - i);
    return max_proizvodnaya * mult / nfac;
}

template<typename realType, typename valueType, indexType N>
const std::array<valueType, N> &NewtonInterpolation<realType, valueType, N>::getDiff(){
    return dividedDifferences_;
}

/**
 * Узлы Чебышева на отрезке [a, b]
 * @tparam N - порядок полинома Чебышева
 */
template <typename realType, indexType N>
std::array<realType, N> getChebyshevNodes(realType a, realType b) {
    using delta = decltype(b - a);

    std::array<realType, N> result;
    const delta mul2 = 0.5 * (b - a);
    const realType mul1 = a + mul2;
    constexpr delta phi = M_PI / N;
    constexpr delta phi_2 = M_PI_2 / N;
    const delta cos1_2 = std::cos(phi_2);
    const delta sin1_2 = std::sin(phi_2);
    const delta cos = std::cos(phi);
    const delta sin = std::sin(phi);

    delta cosk_1 = cos;
    delta sink_1 = sin;

    result[N - 1] = mul1 + mul2 * (cos * cos1_2 + sin * sin1_2);

    for (indexType i = N - 1; i >= 1; i--) {
        delta cosk = cosk_1 * cos - sin * sink_1;
        delta sink = cos * sink_1 + sin * cosk_1;
        result[i - 1] = mul1 + mul2 * (cosk * cos1_2 + sink * sin1_2);
        cosk_1 = cosk;
        sink_1 = sink;
    }
    return result;
}

#endif  // NEWTONINTERPOLATION_HPP_
