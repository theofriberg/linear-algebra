#pragma once

#include "./Matrix.hpp"

class MatrixOperator
{
public:
    MatrixOperator() {}
    Matrix add(const Matrix &m1, const Matrix &m2);
    double hadamard_product(const Matrix &m1, const Matrix &m2);
};