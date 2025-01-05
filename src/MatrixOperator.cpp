#include "../include/MatrixOperator.hpp"
#include "../include/Matrix.hpp"
#include "../include/InvalidMatrixFormat.hpp"

Matrix MatrixOperator::add(const Matrix &m1, const Matrix &m2)
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
            double value = m1.get_element(i, j) + m2.get_element(i, j);
            result.set_element(i, j, value);
        }
    }

    return result;
}

double MatrixOperator::hadamard_product(const Matrix &m1, const Matrix &m2)
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
            result += m1.get_element(i, j) * m2.get_element(i, j);
        }
    }

    return result;
}
