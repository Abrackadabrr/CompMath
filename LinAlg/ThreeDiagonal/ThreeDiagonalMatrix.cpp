//
// Created by evgen on 05.02.2022.
//

#include "ThreeDiagonalMatrix.hpp"
namespace Slae::Matrix{

    ThreeDiagonalMatrix::ThreeDiagonalMatrix(int n): data_(n) {}

    double & ThreeDiagonalMatrix::operator()(int i, int j) {
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

    const double & ThreeDiagonalMatrix::operator()(int i, int j) const {
        return data_[i][j];
    }

    int ThreeDiagonalMatrix::rows() const noexcept {
        return data_.size();
    }

    ThreeDiagonalMatrix ThreeDiagonalMatrix::Identity(int n) {
        ThreeDiagonalMatrix result(n);
        for (auto& string: result.data_) {
            string = {0., 1., 0.};
        }
        return result;
    }

    ThreeDiagonalMatrix ThreeDiagonalMatrix::ThreeDiagonal(int n, double val1, double val2, double val3) {
        ThreeDiagonalMatrix result(n);
        for (auto& string: result.data_) {
            string = {val1, val2, val3};
        }
        return result;
    }

    ThreeDiagonalMatrix ThreeDiagonalMatrix::Zero(int n) {
        ThreeDiagonalMatrix result(n);
        for (auto& string: result.data_) {
            string = {0., 0., 0.};
        }
        return result;
    }
}
