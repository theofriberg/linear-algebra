#include "../include/Matrix.hpp"
#include "../include/InvalidMatrixFormat.hpp"
#include "../include/MatrixView.hpp"
#include "../include/TransposedMatrixView.hpp"

#include <iostream>

/**
 * Finds the smallest integer k >= n such that k == 2^x for some integer x.
 */
int find_smallest_integer_power_of_two(int n)
{
    if (n < 1)
    {
        throw std::invalid_argument("Input must be a positive integer.");
    }

    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}

/**
 * If rows is less then cols we need to add at least as many rows such that
 * the number of rows == number of columns. We then call find_smallest_integer_power_of_two()
 * on the number of columns to find the smallest integer n such that n == 2^x for some integer x.
 */
int find_square_shape(int rows, int cols)
{
    return rows < cols
               ? find_smallest_integer_power_of_two(cols)
               : find_smallest_integer_power_of_two(rows);
}

Matrix::Matrix(int r, int c) : rows(r),
                               cols(c),
                               data(std::shared_ptr<double[]>(new double[r * c](), std::default_delete<double[]>())) {}

Matrix Matrix::transpose() const
{
    int transposed_rows = cols;
    int transposed_cols = rows;

    Matrix transposed(transposed_rows, transposed_cols); // Cols and rows are flipped

    for (int i = 0; i < transposed_rows; i++)
    {
        for (int j = 0; j < transposed_cols; j++)
        {
            transposed(i, j) = get_element(j, i);
        }
    }

    return transposed;
}

TransposedMatrixView Matrix::transpose_view() const
{
    int transposed_rows = cols;
    int transposed_cols = rows;

    return TransposedMatrixView(data, transposed_rows, transposed_cols, 0, 0);
}

/**
 * Note that MatrixView.get_element() will return 0.0 if the row or column index is out of bounds
 * so we only need to find the correct number of rows and columns and return a MatrixView of that shape.
 */
MatrixView Matrix::create_square_view() const
{
    int shape = find_square_shape(rows, cols);
    return MatrixView(data, shape, shape, 0, 0);
}

// This function should not be used in production code. Only for testing/debugging purposes.
void Matrix::set_data(const std::vector<std::vector<double>> &newData)
{
    if (newData.size() != rows)
    {
        throw InvalidMatrixFormat("Number of rows in input data does not match number of rows in matrix.");
    }

    for (int i = 0; i < rows; i++)
    {
        if (newData[i].size() != cols)
        {
            throw InvalidMatrixFormat("Number of columns in input data does not match number of columns in matrix.");
        }

        for (int j = 0; j < cols; j++)
        {
            set_element(i, j, newData[i][j]);
        }
    }
}

double &Matrix::operator()(int row, int col)
{
    if (!is_valid_index(row, col))
    {
        throw std::out_of_range("Matrix index out of bounds.");
    }

    return data[row * cols + col];
}

const double &Matrix::operator()(int row, int col) const
{
    if (!is_valid_index(row, col))
    {
        throw std::out_of_range("Matrix index out of bounds.");
    }

    return data[row * cols + col];
}

Matrix Matrix::operator+(const Matrix &other) const
{
    if (rows != other.get_rows() || cols != other.get_cols())
    {
        throw InvalidMatrixFormat("Invalid format for matrix addition. Number of rows and number of columns must match.");
    }

    Matrix result(rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result(i, j) = get_element(i, j) + other(i, j);
        }
    }

    return result;
}

Matrix Matrix::operator-(const Matrix &other) const
{
    if (rows != other.get_rows() || cols != other.get_cols())
    {
        throw InvalidMatrixFormat("Invalid format for matrix addition. Number of rows and number of columns must match.");
    }

    Matrix result(rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result(i, j) = get_element(i, j) - other(i, j);
        }
    }

    return result;
}

void Matrix::set_element(int row, int col, double val)
{
    if (!is_valid_index(row, col))
    {
        throw std::out_of_range("Matrix index out of bounds.");
    }

    data[row * cols + col] = val;
}

double Matrix::get_element(int row, int col) const
{
    if (!is_valid_index(row, col))
    {
        throw std::out_of_range("Matrix index out of bounds.");
    }

    return data[row * cols + col];
}

int Matrix::get_rows() const
{
    return rows;
}

int Matrix::get_cols() const
{
    return cols;
}

bool Matrix::is_valid_index(int row, int col) const
{
    return row >= 0 && row < rows && col >= 0 && col < cols;
}
