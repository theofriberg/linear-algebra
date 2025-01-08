#pragma once

#include "../include/MatrixView.hpp"

#include <memory>

class TransposedMatrixView : public MatrixView
{
public:
    TransposedMatrixView(std::shared_ptr<const double[]> data, int r, int c, int row_off, int col_off)
        : MatrixView(data, r, c, row_off, col_off) {}

    /**
     * @brief Returns the element at the specified row and column in the transposed matrix view.
     *
     * This function simulates accessing an element in a transposed matrix by reversing the row and column indices.
     * It calls the base class (MatrixView) to retrieve the element at the transposed position.
     *
     * @param row The row index in the transposed matrix view.
     * @param col The column index in the transposed matrix view.
     *
     * @return The element at the specified row and column in the transposed matrix view.
     */
    double get_element(int row, int col) const override;
};