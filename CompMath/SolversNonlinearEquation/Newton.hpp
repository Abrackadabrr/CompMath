//
// Created by evgen on 11.10.2022.
//

#include "LinAlg/dense_matrix/Densematrix.hpp"
#include "LinAlg/vectors/Norm.hpp"
#include "LinAlg/vectors/Vectors.hpp"

#include <optional>
#include <functional>

template<int N>
std::optional<std::vector<double>>
Newton(const std::vector<double> &initial_approximation,
       const std::function<Slae::Matrix::DenseMatrix<double>(std::vector<double>)> &inverse_jacobi_matrix_function,
       const std::function<std::vector<double>(std::vector<double>)> &function, double tolerance) {
    std::vector<double> result = initial_approximation;
    int n = 0;
    double residual = norm(function(result), NormType::InfNorm);
    while (residual > tolerance) {
        n++;
        const auto previous = result;
        result = result - inverse_jacobi_matrix_function(result) * function(result);
        residual = norm(function(result), NormType::InfNorm);
        if (residual > 100000) return std::optional<std::vector<double>>();
    }
    return result;
}
