//
// Created by evgen on 11.10.2022.
//

#include <iostream>

#include "LinAlg/dense_matrix/Densematrix.hpp"
#include "CompMath/SolversNonlinearEquation/Newton.hpp"

Slae::Matrix::DenseMatrix<double> jacobi_function(std::vector<double> x) {
    Slae::Matrix::DenseMatrix<double> result(2, 2);
    const double cos2 = std::cos(x[0]) * std::cos(x[0]);
    const double det = 2*x[0]*x[1] + 2*x[1]/cos2;
    result(0, 0) = x[1] / det;
    result(0, 1) = - 2 * x[1] / det;
    result(1, 0) = 1 / cos2 / det;
    result(1, 1) = 2 * x[0] / det;
    return result;
}

std::vector<double> function(std::vector<double> x) {
    std::vector<double> result(2, 0);
    result[0] = x[0] * x[0] + x[1] * x[1] - 1;
    result[1] = x[1] - std::tan(x[0]);
    return result;
}

int main() {
    // корни располагаются в областях [-0.7; -0.6] X [-0.8; -0.7] и [0.6; 0.7] X [0.7; 0.8]
    // тогда и начальные приближения соответвующие

    std::cout << "Решения тектовой задачи 1" << std::endl;
    std::vector<double> initial_approx{0.6, 0.7};
    const auto result = Newton<2>(initial_approx, jacobi_function, function, 1e-10);
    std::cout.precision(10);
    if (result.has_value())
        std::cout << result.value() << std::endl;
    else std::cout << "Расходимся, ребята, в первом случае все печально" << std::endl;
    std::vector<double> initial_approx2{-1, -1};
    const auto result2 = Newton<2>(initial_approx2, jacobi_function, function, 1e-12);
    if (result2.has_value())
        std::cout << result2.value() << std::endl;
    else std::cout << "Расходимся, ребята, во втором случае все печально" << std::endl;
    return 0;
}