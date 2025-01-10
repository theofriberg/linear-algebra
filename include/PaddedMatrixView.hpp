#pragma once

#include "../include/MatrixView.hpp"

#include <memory>

class PaddedMatrixView : public MatrixView
{
public:
    PaddedMatrixView(std::shared_ptr<const double[]> data, int r, int c, int p_rows, int p_cols);

    double get_element(int row, int col) const override;

private:
    int rows;
    int cols;
    int parent_rows;
    int parent_cols;
};