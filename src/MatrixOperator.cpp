#include "../include/MatrixOperator.hpp"
#include "../include/Matrix.hpp"
#include "../include/InvalidMatrixFormat.hpp"

Matrix MatrixOperator::add(const Matrix &m1, const Matrix &m2)
{
    if (m1.getRows() != m2.getRows() || m1.getCols() != m2.getCols())
    {
        throw InvalidMatrixFormat("Invalid format for matrix addition. Number of rows and number of columns must match.");
    }

    int result_rows = m1.getRows();
    int result_cols = m1.getCols();

    Matrix result(result_rows, result_cols);
    for (int i = 0; i < result_rows; i++)
    {
        for (int j = 0; j < result_cols; j++)
        {
            double value = m1.getElement(i, j) + m2.getElement(i, j);
            result.setElement(i, j, value);
        }
    }

    return result;
}

double MatrixOperator::hadamardProduct(const Matrix &m1, const Matrix &m2)
{
    if (m1.getRows() != m2.getRows() || m1.getCols() != m2.getCols())
    {
        throw InvalidMatrixFormat("Invalid format for matrix addition. Number of rows and number of columns must match.");
    }

    double result = 0;

    for (int i = 0; i < m1.getRows(); i++)
    {
        for (int j = 0; j < m1.getCols(); j++)
        {
            result += m1.getElement(i, j) * m2.getElement(i, j);
        }
    }

    return result;
}
