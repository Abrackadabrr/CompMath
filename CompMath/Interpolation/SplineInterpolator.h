//
// Created by evgen on 27.09.2022.
//

#ifndef LABS_COMP_MATH_SPLINEINTERPOLATOR_H
#define LABS_COMP_MATH_SPLINEINTERPOLATOR_H

#include "LinAlg/ThreeDiagonal/ThreeDiagonalMatrix.hpp"
#include "LinAlg/ThreeDiagonal/ThreeDiagonalSolver.hpp"
#include "LinAlg/vectors/Vectors.hpp"


/***
 * Естественный одномерный кубический сплайн
 * @tparam N - количество точек в шаблоне
 */
template<int N>
class CubicSplineInterpolator {

    using matrix = Slae::Matrix::ThreeDiagonalMatrix<double>;

    static_assert(N >= 2);
private:
    std::array<double, N> xData;
    std::array<double, N - 1> a;
    std::array<double, N - 1> b;
    std::array<double, N - 1> c;
    std::array<double, N - 1> d;

public:
    CubicSplineInterpolator(std::array<double, N> x, std::array<double, N> f) : xData(x) {
        std::copy(f.begin() + 1, f.begin() + N, a.begin());
        matrix A = matrix::ThreeDiagonal(N - 2, 0., 2., 0.);

        /** формирование массива разностей аргументов сетки **/
        std::array<double, N - 1> h{};
        for (int i = 1; i < N; i++) {
            h[i - 1] = x[i] - x[i - 1];
        }

        /** формирование матрицы **/
        A(0, 2) = h[1] / (h[1] + h[0]);
        for (int i = 1; i < N - 3; i++) {
            A(i, 0) = h[i] / (h[i] + h[i + 1]);
            A(i, 2) = h[i + 1] / (h[i] + h[i + 1]);
        }
        A(N - 3, 0) = h[N - 3] / (h[N - 3] + h[N - 2]);

        /** вычисление разделенных разностей **/
        std::array<double, N - 1> f_1{};
        std::vector<double> f_2(N - 2);
        f_1[0] = (f[1] - f[0]) / h[0];
        for (int i = 2; i < N; i++) {
            f_1[i - 1] = (f[i] - f[i - 1]) / h[i - 1];
            f_2[i - 2] = (f_1[i-1] - f_1[i - 2]) / (h[i - 2] + h[i-1]);
        }

        /** нахождение коэффициентов с **/
        const auto result_c = Slae::Solvers::solveThreeDiagonal(A, 6 * f_2);
        std::copy(result_c.begin(), result_c.end(), c.begin());
        c[N - 2] = 0;  // условие естественного сплайна

        /** нахождение коэффициентов b, d **/
        b[0] = ((c[0] * h[0]) / 3) + f_1[0];
        d[0] = c[0] / h[0];  // условие естественного сплайна
        for (int i = 1; i < N - 1; i++) {
            b[i] = ((c[i] * h[i]) / 3) + ((c[i-1] * h[i]) / 6) + f_1[i];
            d[i] = (1 / h[i]) * (c[i] - c[i - 1]);
        }
    }

    [[nodiscard]] double interpolate(double x) const{
        for (int i = 0; i < N; i++) {
            if (x < xData[i] && i != 0) {
                const double arg = (x - xData[i]);
                const double arg2 = arg * arg;
                const double arg3 = arg2 * arg;
                return a[i-1] + b[i-1] * arg + (c[i-1]/2) * arg2 + (d[i-1]/6) * arg3;
             }
        }
        throw std::exception();
    }

    double extrapolate(double x) const{
        if (x > xData.back()){
            const double arg = (x - xData.back());
            const double arg2 = arg * arg;
            const double arg3 = arg2 * arg;
            return a.back() + b.back() * arg + (c.back()/2) * arg2 + (d.back()/6) * arg3;
        }
    }

    double interpErrorUniformGrid(double x, double max_proizvodnaya, double h) {
        return (max_proizvodnaya / 24) * (h*h*h*h / 16);
    }
};

#endif //LABS_COMP_MATH_SPLINEINTERPOLATOR_H
