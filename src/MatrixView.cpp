#include "../include/MatrixView.hpp"

MatrixView::MatrixView(const double *data, int r, int c, int row_off, int col_off)
    : parent_data(data), rows(r), cols(c), row_offset(row_off), col_offset(col_off) {}

double MatrixView::get_element(int row, int col) const
{
    return parent_data[(row + row_offset) * cols + col + col_offset];
}

int MatrixView::get_rows() const
{
    return rows;
}

int MatrixView::get_cols() const
{
    return cols;
}