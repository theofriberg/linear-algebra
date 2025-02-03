#pragma once

#include "./Matrix.hpp"

class MatrixOperator
{
public:
    MatrixOperator() {}

    /**
     * @brief Adds two matrices element-wise.
     *
     * This function takes two matrices as input and returns a new matrix.
     * Each element in the new matrix is the sum of the corresponding elements in the input matrices.
     *
     * @param m1 The first input matrix.
     * @param m2 The second input matrix.
     *
     * @return A new matrix containing the element-wise sum of m1 and m2.
     *
     * @throws InvalidMatrixFormat If the input matrices have different dimensions.
     *
     * @note The input matrices must have the same dimensions.
     */
    Matrix add(const Matrix &m1, const Matrix &m2) const;

    Matrix matmul(const Matrix &m1, const Matrix &m2) const;

    /**
     * @brief Calculates the Hadamard product of two matrices.
     *
     * The Hadamard product of two matrices is a new matrix obtained by multiplying corresponding elements of the input matrices.
     * This function takes two matrices as input and returns the result of the Hadamard product.
     *
     * @param m1 The first input matrix.
     * @param m2 The second input matrix.
     *
     * @return The result of the Hadamard product of the input matrices.
     *
     * @throws InvalidMatrixFormat If the input matrices have different dimensions.
     *
     * @note The Hadamard product is only defined for matrices of the same dimensions.
     */
    double hadamard_product(const Matrix &m1, const Matrix &m2) const;

    MatrixView merge_top_bottom(const MatrixView &m1_view, const MatrixView &m2_view) const;

    MatrixView merge_side_to_side(const MatrixView &m1_view, const MatrixView &m2_view) const;

private:
    const int STRASSEN_THRESHOLD = 0;

    /**
     * @brief Performs matrix multiplication using Strassen's algorithm if the number of rows in the first matrix is greater than the given threshold.
     *        Otherwise, it uses the naive matrix multiplication algorithm.
     *
     * @param m1 The first matrix.
     * @param m2 The second matrix.
     * @param threshold The threshold value for switching between Strassen's algorithm and the naive algorithm.
     *
     * @return The result of the matrix multiplication.
     *
     * @throws InvalidMatrixFormat If the number of columns in the first matrix does not match the number of rows in the second matrix.
     *
     * @note This function assumes that the matrices are square and have dimensions that are powers of 2.
     */
    Matrix strassen(const Matrix &m1, const Matrix &m2, int threshold) const;

    MatrixView strassen(const MatrixView &m1_view, const MatrixView &m2_view, int threshold) const;

    /**
     * @brief Performs matrix multiplication using the naive algorithm.
     *
     * This function takes two matrices as input and returns a new matrix.
     * Each element in the new matrix is the sum of the products of corresponding elements in the input matrices.
     *
     * @param m1 The first input matrix.
     * @param m2 The second input matrix.
     *
     * @return A new matrix containing that is the matrix product of the two matrices.
     */
    Matrix naive_matmul(const Matrix &m1, const Matrix &m2) const;

    MatrixView naive_matmul(const MatrixView &m1_view, const MatrixView &m2_view) const;
};