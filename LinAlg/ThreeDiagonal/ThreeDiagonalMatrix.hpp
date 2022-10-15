//
// Created by evgen on 05.02.2022.
//

#ifndef MY_PROJECT_THREEDIAGONALMATRIX_HPP
#define MY_PROJECT_THREEDIAGONALMATRIX_HPP

#include <vector>
#include <array>
#include <sstream>
#include "set"

namespace Slae::Matrix{
    /**
     * @brief Class of special type of matrix: matrix with three diagonal
     *
     * Elements in matrix almost equal zero, except of elements on the main diagonal
     * and diagonals that are above and below it. So there is a special type of holding these values.
     */
     template<typename valueType>
    class ThreeDiagonalMatrix {
    private:
        std::vector<std::array<valueType, 3>> data_;
    public:

        /** @brief ThreeDiagonalMatrix static 'constructor'
         * Creates three-diagonal matrix with size 'size' and fill it by zeros
         *
         * @param size Matrix size
         *
         * @return zero-filled size-sized ThreeDiagonalMatrix instance
         */
        static ThreeDiagonalMatrix Zero(int n);

        /** @brief ThreeDiagonalMatrix static 'constructor'
         * Creates three-diagonal matrix with size 'size' and fill it by ones on main diagonal
         *
         * @param size Matrix size
         *
         * @return ThreeDiagonalMatrix instance
         */
        static ThreeDiagonalMatrix Identity(int n);

       /** @brief ThreeDiagonalMatrix class constructor
        *
        * Creates three-diagonal matrix with size 'size'
        * @warning You shouldn't use this instance without set all of elements with special methods
        * @see  operator()(int i, int j) Zero(int n) ThreeDiagonal(int n, valueType val1, valueType val2, valueType val3)
        *
        * @param size Matrix instance size
        */
        explicit ThreeDiagonalMatrix(int n);

        /** @brief Access operator
         *
         * @return &(i, j) element of three-diagonal matrix; i means number of row, j belongs to {0, 1, 2}
         *
         * @param i  Number of row, belongs to {0,..., matrix size - 1}
         *
         * @param j  One of diagonal elements in a row i; j belongs to {0, 1, 2} === {below, main, above}
         *
         * @warning If you try to access (0, 0) or (matrix size - 1, 2) elements, exception will be thrown
         * because elements with these indexes don't exist.
         *
         * @throw SlaeBaseExceptionCpp if indexes are incorrect
         */
        valueType & operator()(int i, int j);

        /** @brief Access operator
         *
         * @return const &(i, j) element of three-diagonal matrix; i means number of row, j belongs to {0, 1, 2}
         *
         * @param i  Number of row, belongs to {0,..., matrix size - 1}
         *
         * @param j  One of diagonal elements in a row i; j belongs to {0, 1, 2} === {below, main, above}
         *
         * @warning If you try to access (0, 0) or (matrix size - 1, 2) elements, exception will be thrown
         * because elements with these indexes don't exist.
         *
         * @throw SlaeBaseExceptionCpp if indexes are incorrect
         */
        [[nodiscard]] const valueType & operator()(int i, int j) const;

        /** @brief
         *
         * @return matrix row-size
        */
        [[nodiscard]] int rows() const noexcept;

        static ThreeDiagonalMatrix ThreeDiagonal(int n, valueType val1, valueType val2, valueType val3);
    };

    template<typename valueType>
    ThreeDiagonalMatrix<valueType>::ThreeDiagonalMatrix(int n): data_(n) {}

    template<typename valueType>
    valueType & ThreeDiagonalMatrix<valueType>::operator()(int i, int j) {
#ifndef NDEBUG
        if (i >= data_.size()) {

        }
        if (j > 2) {

        }
        if ((i == 0 && j == 0) || (i == data_.size() - 1 && j == 2)) {

        }
#endif //NDEBUG
        return data_[i][j];
    }

    template<typename valueType>
    const valueType & ThreeDiagonalMatrix<valueType>::operator()(int i, int j) const {
        return data_[i][j];
    }

    template<typename valueType>
    int ThreeDiagonalMatrix<valueType>::rows() const noexcept {
        return data_.size();
    }

    template<typename valueType>
    ThreeDiagonalMatrix<valueType> ThreeDiagonalMatrix<valueType>::Identity(int n) {
        ThreeDiagonalMatrix result(n);
        for (auto& string: result.data_) {
            string = {0., 1., 0.};
        }
        return result;
    }

    template<typename valueType>
    ThreeDiagonalMatrix<valueType> ThreeDiagonalMatrix<valueType>::ThreeDiagonal(int n, valueType val1, valueType val2, valueType val3) {
        ThreeDiagonalMatrix result(n);
        for (auto& string: result.data_) {
            string = {val1, val2, val3};
        }
        return result;
    }

    template<typename valueType>
    ThreeDiagonalMatrix<valueType> ThreeDiagonalMatrix<valueType>::Zero(int n) {
        ThreeDiagonalMatrix result(n);
        for (auto& string: result.data_) {
            string = {0., 0., 0.};
        }
        return result;
    }
}  //  namespace Slae::Matrix

#endif //MY_PROJECT_THREEDIAGONALMATRIX_HPP
