#include "../include/MatrixView.hpp"
#include "../include/TransposedMatrixView.hpp"

/**
 * Calls base class MatrixView with rows and cols in the reversed order,
 * thus simulating a transposed matrix.
 */
double TransposedMatrixView::get_element(int row, int col) const
{
    return MatrixView::parent_data[(col + MatrixView::col_offset) * rows + row + MatrixView::row_offset];
}
