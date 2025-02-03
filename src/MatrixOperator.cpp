#include "../include/MatrixOperator.hpp"
#include "../include/Matrix.hpp"
#include "../include/InvalidMatrixFormat.hpp"

Matrix MatrixOperator::add(const Matrix &m1, const Matrix &m2) const
{
    if (m1.get_rows() != m2.get_rows() || m1.get_cols() != m2.get_cols())
    {
        throw InvalidMatrixFormat("Invalid format for matrix addition. Number of rows and number of columns must match.");
    }

    int result_rows = m1.get_rows();
    int result_cols = m1.get_cols();

    Matrix result(result_rows, result_cols);
    for (int i = 0; i < result_rows; i++)
    {
        for (int j = 0; j < result_cols; j++)
        {
            result(i, j) = m1(i, j) + m2(i, j);
        }
    }

    return result;
}

Matrix MatrixOperator::matmul(const Matrix &m1, const Matrix &m2) const
{
    if (m1.get_cols() != m2.get_rows())
    {
        throw InvalidMatrixFormat("Invalid format for matrix multiplication. Number of columns in the first matrix must match the number of rows in the second matrix.");
    }

    return strassen(m1, m2, STRASSEN_THRESHOLD);
}

double MatrixOperator::hadamard_product(const Matrix &m1, const Matrix &m2) const
{
    if (m1.get_rows() != m2.get_rows() || m1.get_cols() != m2.get_cols())
    {
        throw InvalidMatrixFormat("Invalid format for matrix addition. Number of rows and number of columns must match.");
    }

    double result = 0;

    for (int i = 0; i < m1.get_rows(); i++)
    {
        for (int j = 0; j < m1.get_cols(); j++)
        {
            result += m1(i, j) * m2(i, j);
        }
    }

    return result;
}

MatrixView MatrixOperator::merge_top_bottom(const MatrixView &m1_view, const MatrixView &m2_view) const
{
    if (m1_view.get_cols() != m2_view.get_cols())
    {
        throw InvalidMatrixFormat("Matrices must have the same number of columns to merge top to bottom.");
    }

    int result_rows = m1_view.get_rows() + m2_view.get_rows();
    int result_cols = m1_view.get_cols();

    std::shared_ptr<double[]> result_data(new double[result_rows * result_cols]());
    for (int i = 0; i < result_rows; i++)
    {
        for (int j = 0; j < result_cols; j++)
        {
            result_data[i * result_cols + j] = i < m1_view.get_rows()
                                                   ? m1_view.get_element(i, j)
                                                   : m2_view.get_element(i - m1_view.get_rows(), j);
        }
    }

    return MatrixView(result_data, result_rows, result_cols, 0, 0);
}

MatrixView MatrixOperator::merge_side_to_side(const MatrixView &m1_view, const MatrixView &m2_view) const
{
    if (m1_view.get_rows() != m2_view.get_rows())
    {
        throw InvalidMatrixFormat("Matrices must have the same number of rows to merge side to side.");
    }

    int result_rows = m1_view.get_rows();
    int result_cols = m1_view.get_cols() + m2_view.get_cols();

    std::shared_ptr<double[]> result_data(new double[result_rows * result_cols](), std::default_delete<double[]>());
    for (int i = 0; i < result_rows; i++)
    {
        for (int j = 0; j < result_cols; j++)
        {
            result_data[i * result_cols + j] = j < m1_view.get_cols()
                                                   ? m1_view.get_element(i, j)
                                                   : m2_view.get_element(i, j - m1_view.get_cols());
        }
    }

    return MatrixView(result_data, result_rows, result_cols, 0, 0);
}

Matrix MatrixOperator::strassen(const Matrix &m1, const Matrix &m2, int threshold) const
{
    if (m1.get_rows() <= threshold)
    {
        return naive_matmul(m1, m2);
    }

    MatrixView m1_view = m1.create_square_view();
    MatrixView m2_view = m2.create_square_view();

    std::array<MatrixView, 4> m1_submatrices = m1_view.split();
    std::array<MatrixView, 4> m2_submatrices = m2_view.split();

    MatrixView p1_view = strassen(m1_submatrices[0] + m1_submatrices[3], m2_submatrices[0] + m2_submatrices[3], threshold);
    MatrixView p2_view = strassen(m1_submatrices[2] + m1_submatrices[3], m2_submatrices[0], threshold);
    MatrixView p3_view = strassen(m1_submatrices[0], m2_submatrices[1] - m2_submatrices[3], threshold);
    MatrixView p4_view = strassen(m1_submatrices[3], m2_submatrices[2] - m2_submatrices[0], threshold);
    MatrixView p5_view = strassen(m1_submatrices[0] + m1_submatrices[1], m2_submatrices[3], threshold);
    MatrixView p6_view = strassen(m1_submatrices[2] - m1_submatrices[0], m2_submatrices[0] + m2_submatrices[1], threshold);
    MatrixView p7_view = strassen(m1_submatrices[1] - m1_submatrices[3], m2_submatrices[2] + m2_submatrices[3], threshold);

    MatrixView c11_12_view = merge_side_to_side(p1_view + p4_view - p5_view + p7_view, p3_view + p5_view);
    MatrixView c21_22_view = merge_side_to_side(p2_view + p4_view, p1_view - p2_view + p3_view + p6_view);

    MatrixView padded_result_view = merge_top_bottom(c11_12_view, c21_22_view);

    return padded_result_view.convert_to_matrix(0, m1.get_rows(), 0, m2.get_cols());
}

MatrixView MatrixOperator::strassen(const MatrixView &m1_view, const MatrixView &m2_view, int threshold) const
{
    if (m1_view.get_rows() <= threshold)
    {
        return naive_matmul(m1_view, m2_view);
    }

    std::array<MatrixView, 4> m1_submatrices = m1_view.split();
    std::array<MatrixView, 4> m2_submatrices = m2_view.split();

    MatrixView p1_view = strassen(m1_submatrices[0] + m1_submatrices[3], m2_submatrices[0] + m2_submatrices[3], threshold);
    MatrixView p2_view = strassen(m1_submatrices[2] + m1_submatrices[3], m2_submatrices[0], threshold);
    MatrixView p3_view = strassen(m1_submatrices[0], m2_submatrices[1] - m2_submatrices[3], threshold);
    MatrixView p4_view = strassen(m1_submatrices[3], m2_submatrices[2] - m2_submatrices[0], threshold);
    MatrixView p5_view = strassen(m1_submatrices[0] + m1_submatrices[1], m2_submatrices[3], threshold);
    MatrixView p6_view = strassen(m1_submatrices[2] - m1_submatrices[0], m2_submatrices[0] + m2_submatrices[1], threshold);
    MatrixView p7_view = strassen(m1_submatrices[1] - m1_submatrices[3], m2_submatrices[2] + m2_submatrices[3], threshold);

    MatrixView c11_12_view = merge_side_to_side(p1_view + p4_view - p5_view + p7_view, p3_view + p5_view);
    MatrixView c21_22_view = merge_side_to_side(p2_view + p4_view, p1_view - p2_view + p3_view + p6_view);

    MatrixView padded_result_view = merge_top_bottom(c11_12_view, c21_22_view);

    return padded_result_view;
}

Matrix MatrixOperator::naive_matmul(const Matrix &m1, const Matrix &m2) const
{
    int result_cols = m1.get_cols();
    int result_rows = m2.get_rows();

    Matrix result(result_rows, result_cols);
    for (int i = 0; i < result_rows; i++)
    {
        for (int j = 0; j < result_cols; j++)
        {
            double value = 0;
            for (int k = 0; k < m1.get_cols(); k++)
            {
                value += m1(i, k) * m2(k, j);
            }
            result(i, j) = value;
        }
    }

    return result;
}

MatrixView MatrixOperator::naive_matmul(const MatrixView &m1_view, const MatrixView &m2_view) const
{
    int result_rows = m1_view.get_rows();
    int result_cols = m2_view.get_cols();

    std::shared_ptr<double[]> result_data(new double[result_rows * result_cols]());
    for (int i = 0; i < result_rows; i++)
    {
        for (int j = 0; j < result_cols; j++)
        {
            double value = 0;
            for (int k = 0; k < m1_view.get_cols(); k++)
            {
                value += m1_view.get_element(i, k) * m2_view.get_element(k, j);
            }
            result_data[i * result_cols + j] = value;
        }
    }

    return MatrixView(result_data, result_rows, result_cols, 0, 0);
}
