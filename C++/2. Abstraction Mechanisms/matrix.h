// ======================================================================
// matrix.h
// 
// Generic Matrix class template (fixed dimensions).
// Supports:
// - Element access via operator()
// - Addition, subtraction, scalar multiplication
// - Output stream
// Demonstrates non-type template parameters and template composition.
// ======================================================================

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>
#include "array.h"   // for fixed-size storage

template<typename T, std::size_t Rows, std::size_t Cols>
class Matrix {
public:
    // Default constructor: zero-initialize
    Matrix() = default;

    // Element access
    T& operator()(std::size_t r, std::size_t c) {
        if (r >= Rows || c >= Cols) throw std::out_of_range("Matrix index out of range");
        return data_[r * Cols + c];
    }
    const T& operator()(std::size_t r, std::size_t c) const {
        if (r >= Rows || c >= Cols) throw std::out_of_range("Matrix index out of range");
        return data_[r * Cols + c];
    }

    // Matrix addition
    Matrix operator+(const Matrix& other) const {
        Matrix result;
        for (std::size_t i = 0; i < Rows * Cols; ++i)
            result.data_[i] = data_[i] + other.data_[i];
        return result;
    }

    // Matrix subtraction
    Matrix operator-(const Matrix& other) const {
        Matrix result;
        for (std::size_t i = 0; i < Rows * Cols; ++i)
            result.data_[i] = data_[i] - other.data_[i];
        return result;
    }

    // Scalar multiplication (template member? We'll make it a friend)
    friend Matrix operator*(const T& scalar, const Matrix& m) {
        Matrix result;
        for (std::size_t i = 0; i < Rows * Cols; ++i)
            result.data_[i] = scalar * m.data_[i];
        return result;
    }
    friend Matrix operator*(const Matrix& m, const T& scalar) {
        return scalar * m;
    }

    // Output
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        for (std::size_t r = 0; r < Rows; ++r) {
            os << "[ ";
            for (std::size_t c = 0; c < Cols; ++c)
                os << m(r, c) << ' ';
            os << "]\n";
        }
        return os;
    }

private:
    Array<T, Rows * Cols> data_;   // flattened storage
};

#endif // MATRIX_H