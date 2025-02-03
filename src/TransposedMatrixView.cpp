#include "../include/MatrixView.hpp"
#include "../include/TransposedMatrixView.hpp"

TransposedMatrixView::TransposedMatrixView(std::shared_ptr<const double[]> data, int r, int c, int row_off, int col_off)
    : MatrixView(data, r, c, row_off, col_off) {}

/**
 * Calls base class MatrixView with rows and cols in the reversed order,
 * thus simulating a transposed matrix.
 */
double TransposedMatrixView::get_element(int row, int col) const
{
    return MatrixView::parent_data[(col + MatrixView::col_offset) * rows + row + MatrixView::row_offset];
}
