#include <vector>

class Matrix
{
public:
    int rows, cols;
    std::vector<std::vector<double>> data;

    Matrix(int r, int c);
    Matrix add(const Matrix &other);
};