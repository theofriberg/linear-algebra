#include <gtest/gtest.h>

#include "../include/Matrix.hpp"
#include "../include/MatrixOperator.hpp"
#include "../include/InvalidMatrixFormat.hpp"

#include <vector>

TEST(PlaceHolderTest, PlaceHolder)
{
    EXPECT_EQ(1, 1);
}

TEST(MatrixOperatorTest, AdditionPositiveNumbers)
{
    MatrixOperator matrixOperator;

    Matrix A(2, 3);
    Matrix B(2, 3);

    std::vector<std::vector<double>> AData = {{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<double>> BData = {{7, 8, 9}, {10, 11, 12}};

    A.set_data(AData);
    B.set_data(BData);

    Matrix C = matrixOperator.add(A, B);

    for (int i = 0; i < C.get_rows(); i++)
    {
        for (int j = 0; j < C.get_cols(); j++)
        {
            EXPECT_EQ(C.get_element(i, j), A.get_element(i, j) + B.get_element(i, j));
        }
    }
}

TEST(MatrixOperatorTest, AdditionNegativeNumbers)
{
    MatrixOperator matrixOperator;

    Matrix A(2, 3);
    Matrix B(2, 3);

    std::vector<std::vector<double>> AData = {{-1, -2, -3}, {-4, -5, -6}};
    std::vector<std::vector<double>> BData = {{-7, -8, -9}, {-10, -11, -12}};

    A.set_data(AData);
    B.set_data(BData);

    Matrix C = matrixOperator.add(A, B);

    for (int i = 0; i < C.get_rows(); i++)
    {
        for (int j = 0; j < C.get_cols(); j++)
        {
            EXPECT_EQ(C.get_element(i, j), AData[i][j] + BData[i][j]);
        }
    }
}

TEST(MatrixOperatorTest, ThrowsFormatExceptionAdd)
{
    MatrixOperator matrixOperator;

    Matrix A(2, 3);
    Matrix B(3, 2);

    EXPECT_THROW(matrixOperator.add(A, B), InvalidMatrixFormat);
}

TEST(MatrixOperatorTest, HadamardProductPositiveNumbers)
{
    MatrixOperator matrixOperator;

    Matrix A(2, 3);
    Matrix B(2, 3);

    std::vector<std::vector<double>> AData = {{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<double>> BData = {{7, 8, 9}, {10, 11, 12}};

    A.set_data(AData);
    B.set_data(BData);

    double product = matrixOperator.hadamard_product(A, B);

    EXPECT_EQ(product, 1 * 7 + 2 * 8 + 3 * 9 + 4 * 10 + 5 * 11 + 6 * 12);
}

TEST(MatrixOperatorTest, HadamardProductNegativeNumbers)
{
    MatrixOperator matrixOperator;

    Matrix A(2, 3);
    Matrix B(2, 3);

    std::vector<std::vector<double>> AData = {{-1, -2, -3}, {-4, -5, -6}};
    std::vector<std::vector<double>> BData = {{7, 8, 9}, {10, 11, 12}};

    A.set_data(AData);
    B.set_data(BData);

    double product = matrixOperator.hadamard_product(A, B);

    EXPECT_EQ(product, -1 * 7 - 2 * 8 - 3 * 9 - 4 * 10 - 5 * 11 - 6 * 12);
}

TEST(MatrixOperatorTest, ThrowsFormatExceptionHadamard)
{
    MatrixOperator matrixOperator;

    Matrix A(2, 3);
    Matrix B(3, 2);

    EXPECT_THROW(matrixOperator.hadamard_product(A, B), InvalidMatrixFormat);
}
