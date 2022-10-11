//
// Created by petrov on 12.02.2022.
//

#ifndef SLAE_DENSEMATRIX_HPP
#define SLAE_DENSEMATRIX_HPP

#include <vector>
#include <ostream>

namespace Slae::Matrix {
    template<typename T>
    class DenseMatrix {
    public:
        using elm_t = T;
        using idx_t = std::size_t;

    private:
        std::vector<T> matrix_;
        idx_t row_size_, col_size_;

    public:

        /***
         *
         * @param h
         * @param w
         */
        DenseMatrix(const idx_t &h, const idx_t &w);

        DenseMatrix(const DenseMatrix<T> &matrix);

        /***
         *
         * @param h
         * @param w
         */
        DenseMatrix(const idx_t &h, const idx_t &w, const std::vector<T> &data);

        /***
         * Fills matrix with one value
         * @param h    -- row size
         * @param w    -- col size
         * @param fill -- value
         * @return dense matrix filled by value
         */
        DenseMatrix(const idx_t &h, const idx_t &w, T fill);

        /***
         * Unit matrix
         * @param h -- matrix size
         * @return dense unit matrix
         */
        static DenseMatrix<T> Diag(const idx_t &h, T value);

        /***
         * Non-const access operator
         * @param i
         * @param j
         * @return (i, j) element
         */
        elm_t &operator()(const idx_t &i, const idx_t &j);

        /***
         * Const access operator
         * @param i
         * @param j
         * @return
         */
        const elm_t &operator()(const idx_t &i, const idx_t &j) const;

        /***
         * Returns row size
         * @return row size
         */
        [[nodiscard]] const idx_t &get_row_size() const { return row_size_; }

        /***
         * Column size
         * @return column size
         */
        [[nodiscard]] const idx_t &get_col_size() const { return col_size_; }

        /***
         * Return matrix column with index i
         * @param i column index (i <= col_size, begins from 0)
         * @return vector -- matrix column
         */
        std::vector<T> get_col(unsigned i) const;

        /***
         * Swaps 2 rows
         * @param first
         * @param second
         */
        void swap(const idx_t &first, const idx_t &second);

        /***
        * Deletes last row in matrix
        */
        void deleteLastRow();

        DenseMatrix<T> transpose();

        std::vector<T> operator*(const std::vector<T> &vec) const;

        void write_col(std::vector<T> col, const int& i);
    };
}

// Constructors
template<typename T>
Slae::Matrix::DenseMatrix<T>::DenseMatrix(const idx_t &h, const idx_t &w, T fill): matrix_(h * w, fill), row_size_(h),
                                                                                   col_size_(w) {}

template<typename T>
Slae::Matrix::DenseMatrix<T>::DenseMatrix(const idx_t &h, const idx_t &w, const std::vector<T> &data): matrix_(data),
                                                                                                       row_size_(h),
                                                                                                       col_size_(w) {}

template<typename T>
Slae::Matrix::DenseMatrix<T>::DenseMatrix(const DenseMatrix<T> &matrix): matrix_(matrix.matrix_),
                                                                         row_size_(matrix.row_size_),
                                                                         col_size_(matrix.col_size_) {}

template<typename T>
Slae::Matrix::DenseMatrix<T>::DenseMatrix(const idx_t &h, const idx_t &w): matrix_(h * w), row_size_(h),
                                                                           col_size_(w) {}

// static
template<typename T>
Slae::Matrix::DenseMatrix<T> Slae::Matrix::DenseMatrix<T>::Diag(const idx_t &h, T value) {
    DenseMatrix<T> matrix(h, h, 0);
    for (int i = 0; i < h; i++) matrix.matrix_[i*h + i] = value;
    return matrix;
}

// operators
template<typename T>
std::vector<T> Slae::Matrix::DenseMatrix<T>::operator*(const std::vector<T> &vec) const {
    std::vector<T> result(row_size_, 0);
    for (int i = 0; i < row_size_; i++)
        for (int j = 0; j < col_size_; j++)
            result[i] += matrix_[i * col_size_ + j] * vec[j];

    return result;
}
template<typename T>
const T &Slae::Matrix::DenseMatrix<T>::operator()(const idx_t &i, const idx_t &j) const {
    return matrix_[i * col_size_ + j];
}

/***
 * Matrix output
 * @tparam T
 * @param os
 * @param A
 * @return stream
 */
template<typename T>
std::ostream &operator<<(std::ostream &os, const Slae::Matrix::DenseMatrix<T> &A) {
    for (int i = 0; i < A.get_row_size(); ++i) {
        for (int j = 0; j < A.get_col_size(); ++j)
            os  << A(i, j) << " ";
        os << std::endl;
    }
    return os;
}

/***
 * Dense matrix multiplication
 * this is a weak place, needed to be repair (rewrite multiplication order)
 * @tparam T
 * @param A
 * @param B
 * @return dense matrix -- result of multiplication
 */
template<typename T>
Slae::Matrix::DenseMatrix<T> operator*(const Slae::Matrix::DenseMatrix<T> &A, const Slae::Matrix::DenseMatrix<T> &B) {
    Slae::Matrix::DenseMatrix<T> result(A.get_row_size(), B.get_col_size(), 0);

    for (int i = 0; i < A.get_row_size(); i++) {
        for (int j = 0; j < B.get_col_size(); j++) {
            for (int k = 0; k < A.get_col_size(); k++)
                result(i, j) += A(i, k) * B(k, j);
        }
    }
    return result;
}

template<typename T>
T &Slae::Matrix::DenseMatrix<T>::operator()(const idx_t &i, const idx_t &j) {
    return matrix_[i * col_size_ + j];
}

// methods
template<typename T>
Slae::Matrix::DenseMatrix<T> Slae::Matrix::DenseMatrix<T>::transpose() {
    DenseMatrix<T> tr(col_size_, row_size_);
    for (size_t i = 0; i < row_size_; ++i) {
        for (size_t j = 0; j < col_size_; ++j) {
            tr(j, i) = matrix_[i * col_size_ + j];
        }
    }
    return tr;
}

template<typename T>
void Slae::Matrix::DenseMatrix<T>::write_col(std::vector<T> col, const int& i)
{
    for (int j = 0; j < col.size(); j++){
        matrix_[j * col_size_ + i] = col[j];
    }
}


template<typename T>
void Slae::Matrix::DenseMatrix<T>::deleteLastRow() {
    matrix_.erase(matrix_.end() - col_size_, matrix_.end());
    row_size_--;
}

template<typename T>
void Slae::Matrix::DenseMatrix<T>::swap(const idx_t &first, const idx_t &second) {
    std::vector<T> tmp(col_size_);

    for (int i = 0; i < col_size_; ++i) {
        tmp[i] = matrix_[(first - 1) * col_size_ + i];
    }

    for (int i = 0; i < col_size_; ++i) {
        matrix_[(first - 1) * col_size_ + i] = matrix_[(second - 1) * col_size_ + i];
    }

    for (int i = 0; i < col_size_; ++i) {
        matrix_[(second - 1) * col_size_ + i] = tmp[i];
    }
}

template<typename T>
std::vector<T> Slae::Matrix::DenseMatrix<T>::get_col(unsigned i) const {
    std::vector<T> col(row_size_);

    for (unsigned j = 0; j < row_size_; j++)
        col[j] = matrix_[j * col_size_ + i];
    return col;
}

#endif//SLAE_DENSEMATRIX_HPP
