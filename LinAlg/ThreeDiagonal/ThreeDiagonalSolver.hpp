//
// Created by evgen on 05.02.2022.
//

#ifndef MY_PROJECT_THREEDIAGONALSOLVER_HPP
#define MY_PROJECT_THREEDIAGONALSOLVER_HPP

#include "../ThreeDiagonal/ThreeDiagonalMatrix.hpp"

namespace Slae::Solvers {
    /** @brief The method solves the system of equations using the sweep method
    * Solves a system of linear algebraic equations using the sweep method. You can learn about the sweep method
    * from ... (source link)
    *
    * @param matrix threediagonal matrix
     *
    * @param right_side column
    *
    * @warning Matrix instance must have the property of diagonal dominance.
    * If it have not, instead of real result of SLAE, you wil be given by nan or smth like that
    *
    * @throw SlaeBaseExceptionCpp is thrown if the number of matrix rows and column height do not match
    * @return The result of SLAE
    */
    template<typename valueType>
    std::vector<valueType> solveThreeDiagonal(const Slae::Matrix::ThreeDiagonalMatrix<valueType> &matrix, const std::vector<valueType> &col)
    {
        int n = col.size();

        std::vector<valueType> result(n);

        std::vector<std::array<valueType, 2>> pr(n - 1);

        pr[0][0] = matrix(0,2) / matrix(0,1);

        pr[0][1] = col[0] /  matrix(0, 1);

        for (int i = 1; i < n - 1; ++i){

            pr[i][0] = matrix(i,2) / (matrix(i,1) - matrix(i,0) * pr[i - 1][0]);

            pr[i][1] = (col[i] - matrix(i, 0) * pr[i-1][1]) / (matrix(i,1) - matrix(i,0) * pr[i - 1][0]);

        }

        result[n-1] = (col[n-1] - matrix(n-1, 0) * pr[n-2][1]) / (matrix(n-1,1) - matrix(n-1,0) * pr[n - 2][0]);;

        for (int i = n-2; i >= 0; --i){
            result[i] = pr[i][1] - pr[i][0] * result[i+1];
        }

        return result;
    }
}

#endif //MY_PROJECT_THREEDIAGONALSOLVER_HPP
