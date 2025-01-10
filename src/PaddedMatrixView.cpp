#include "../include/PaddedMatrixView.hpp"

PaddedMatrixView::PaddedMatrixView(std::shared_ptr<const double[]> data, int r, int c, int p_rows, int p_cols)
    : MatrixView(std::move(data), r, c, 0, 0),
      parent_rows(p_rows),
      parent_cols(p_cols),
      rows(r),
      cols(c) {}

double PaddedMatrixView::get_element(int row, int col) const
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        throw std::out_of_range("Matrix Index out of range.");
    }

    return (row < parent_rows && col < parent_cols)
               ? MatrixView::get_element(row, col, parent_cols)
               : 0.0;
}