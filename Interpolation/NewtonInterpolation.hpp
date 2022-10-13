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

#endif  // NEWTONINTERPOLATION_HPP_
