#include <gtest/gtest.h>

#include "../include/Matrix.hpp"
#include "../include/MatrixOperator.hpp"
#include "../include/InvalidMatrixFormat.hpp"

#include <vector>

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

TEST(MatrixOperatorTest, MergeSideToSide)
{
    MatrixOperator mat_operator;

    std::shared_ptr<double[]> data1(new double[4]{0, 1, 1, 2});
    std::shared_ptr<double[]> data2(new double[4]{2, 3, 3, 4});

    MatrixView m1_view(data1, 2, 2, 0, 0);
    MatrixView m2_view(data2, 2, 2, 0, 0);

    MatrixView result = mat_operator.merge_side_to_side(m1_view, m2_view);

    for (int i = 0; i < result.get_rows(); i++)
    {
        for (int j = 0; j < result.get_cols(); j++)
        {
            EXPECT_EQ(result.get_element(i, j), i + j);
        }
    }
}

TEST(MatrixOperatorTest, MergeTopBottom)
{
    MatrixOperator mat_operator;

    std::shared_ptr<double[]> data1(new double[4]{0, 1, 1, 2});
    std::shared_ptr<double[]> data2(new double[4]{2, 3, 3, 4});

    MatrixView m1_view(data1, 2, 2, 0, 0);
    MatrixView m2_view(data2, 2, 2, 0, 0);

    MatrixView result = mat_operator.merge_top_bottom(m1_view, m2_view);

    for (int i = 0; i < result.get_rows(); i++)
    {
        for (int j = 0; j < result.get_cols(); j++)
        {
            EXPECT_EQ(result.get_element(i, j), i + j);
        }
    }
}

TEST(MatrixOperatorTest, MatrixMultiplicationSquareMatrices)
{
    MatrixOperator mat_operator;

    std::vector<std::vector<double>> AData = {{1, 2}, {3, 4}};
    std::vector<std::vector<double>> BData = {{5, 6}, {7, 8}};

    Matrix A(2, 2);
    Matrix B(2, 2);

    A.set_data(AData);
    B.set_data(BData);

    Matrix C = mat_operator.matmul(A, B);

    C.display();

    std::vector<std::vector<double>> expected_data = {{5 + 2 * 7, 6 + 2 * 8}, {3 * 5 + 4 * 7, 3 * 6 + 4 * 8}};

    for (int i = 0; i < C.get_rows(); i++)
    {
        for (int j = 0; j < C.get_cols(); j++)
        {
            EXPECT_EQ(C(i, j), expected_data[i][j]);
        }
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}