#include "../include/MatrixView.hpp"
#include "../include/InvalidMatrixFormat.hpp"
#include "../include/Matrix.hpp"

#include <array>
#include <optional>
#include <iostream>

MatrixView::MatrixView(
    std::shared_ptr<const double[]> data,
    int r,
    int c,
    int row_off,
    int col_off) : parent_data(std::move(data)),
                   rows(r),
                   cols(c),
                   row_offset(row_off),
                   col_offset(col_off) {}

double MatrixView::get_element(int row, int col) const
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        throw std::out_of_range("Row or column index out of range.");
    }

    return parent_data[(row + row_offset) * cols + col + col_offset];
}

/**
 * Overloads get_element to take in an additional parameter to modify the stride.
 * Note that the returned value will be different:
 * return parent_data[(row + row_offset) * stride + col + col_offset];
 */
double MatrixView::get_element(int row, int col, int stride) const
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        throw std::out_of_range("Row or column index out of range.");
    }

    return parent_data[(row + row_offset) * stride + col + col_offset];
}

std::array<MatrixView, 4> MatrixView::split() const
{
    if (rows != cols)
    {
        throw InvalidMatrixFormat("Matrix must be square for splitting.");
    }

    int size = rows / 2;
    MatrixView upper_left(parent_data, size, size, row_offset, col_offset);
    MatrixView upper_right(parent_data, size, size, row_offset, col_offset + size);
    MatrixView lower_left(parent_data, size, size, row_offset + size, col_offset);
    MatrixView lower_right(parent_data, size, size, row_offset + size, col_offset + size);

    return {upper_left, upper_right, lower_left, lower_right};
}

/**
 * row_start, col_start are inclusive, row_end, col_end are exclusive.
 */
Matrix MatrixView::convert_to_matrix(int row_start, int row_end, int col_start, int col_end) const
{
    std::cout << "Row start: " << row_start << " Row end: " << row_end << std::endl;
    std::cout << "Col start: " << col_start << " Col end: " << col_end << std::endl;
    std::cout << "Rows: " << rows << std::endl;

    if (row_start < 0 || row_end > rows || row_end <= row_start)
    {
        throw std::out_of_range("Row index out of range.");
    }
    if (col_start < 0 || col_end > cols || col_end <= col_start)
    {
        throw std::out_of_range("Column index out of range.");
    }

    int result_rows = row_end - row_start;
    int result_cols = col_end - col_start;

    Matrix result(result_rows, result_cols);
    for (int i = 0; i < row_end - row_start; i++)
    {
        for (int j = 0; j < col_end - col_start; j++)
        {
            result(i, j) = get_element(i + row_start, j + col_start);
        }
    }

    return result;
}

MatrixView MatrixView::operator+(const MatrixView &other) const
{
    if (rows != other.rows || cols != other.cols)
    {
        throw InvalidMatrixFormat("Matrices must have the same dimensions for addition.");
    }

    std::shared_ptr<double[]> result_data(new double[rows * cols]());
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result_data[i * cols + j] = get_element(i, j) + other.get_element(i, j);
        }
    }

    return MatrixView(result_data, rows, cols, 0, 0);
}

MatrixView MatrixView::operator-(const MatrixView &other) const
{
    if (rows != other.rows || cols != other.cols)
    {
        throw InvalidMatrixFormat("Matrices must have the same dimensions for subtraction.");
    }

    std::shared_ptr<double[]> result_data(new double[rows * cols]());
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result_data[i * cols + j] = get_element(i, j) - other.get_element(i, j);
        }
    }

    return MatrixView(result_data, rows, cols, 0, 0);
}

void MatrixView::display() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << get_element(i, j) << " ";
        }
        std::cout << std::endl;
    }
}
int MatrixView::get_rows() const
{
    return rows;
}

int MatrixView::get_cols() const
{
    return cols;
}