#pragma once

#include <vector>

class Matrix
{
public:
    Matrix(int r, int c);
    ~Matrix();
    Matrix transpose();
    void setData(const std::vector<std::vector<double>> &newData);
    void setElement(int row, int col, double val);
    double getElement(int row, int col) const;
    int getRows() const;
    int getCols() const;

private:
    int rows, cols;
    double *data;
};