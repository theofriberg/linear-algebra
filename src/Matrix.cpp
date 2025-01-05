#include "../include/Matrix.hpp"
#include "../include/InvalidMatrixFormat.hpp"

Matrix::Matrix(int r, int c) : rows(r), cols(c)
{
    data = new double[r * c]();
}

Matrix::~Matrix()
{
    delete[] data;
}

Matrix Matrix::transpose()
{
    Matrix transposed(cols, rows); // Cols and rows are flipped

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            transposed.set_element(j, i, get_element(i, j));
        }
    }

    return transposed;
}

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

void Matrix::set_element(int col, int row, double val)
{
    data[row * cols + col] = val;
}

double Matrix::get_element(int col, int row) const
{
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