#include "./Matrix.hpp"

class MatrixOperator
{
public:
    MatrixOperator() {}
    Matrix add(const Matrix &m1, const Matrix &m2);
    double hadamardProduct(const Matrix &m1, const Matrix &m2);
};