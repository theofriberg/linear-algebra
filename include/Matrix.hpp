#pragma once

#include <vector>

class Matrix
{
public:
    Matrix(int r, int c);
    ~Matrix();
    Matrix transpose();
    void set_data(const std::vector<std::vector<double>> &newData);
    void set_element(int row, int col, double val);
    double get_element(int row, int col) const;
    int get_rows() const;
    int get_cols() const;

private:
    int rows, cols;
    double *data;
};