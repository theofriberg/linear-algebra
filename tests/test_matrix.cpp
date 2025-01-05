#include <gtest/gtest.h>

#include "../include/Matrix.hpp"
#include "../include/InvalidMatrixFormat.hpp"

TEST(MatrixTest, TestSetElement)
{
    Matrix A(2, 2);
    A.set_element(0, 0, 17.23);

    EXPECT_EQ(A.get_element(0, 0), 17.23);
}

TEST(MatrixTest, TestSetData)
{
    Matrix A(2, 2);

    std::vector<std::vector<double>> data = {{1, 2}, {3, 4}};
    A.set_data(data);

    for (int i = 0; i < A.get_rows(); i++)
    {
        for (int j = 0; j < A.get_cols(); j++)
        {
            EXPECT_EQ(A.get_element(i, j), data[i][j]);
        }
    }
}

TEST(MatrixTest, TestSetElementThrowsFormatException)
{
    Matrix A(2, 2);

    std::vector<std::vector<double>> data1 = {{1, 2}, {3, 4}, {5, 6}};
    std::vector<std::vector<double>> data2 = {{1, 2, 3}, {4, 5, 6}};

    EXPECT_THROW(A.set_data(data1), InvalidMatrixFormat);
    EXPECT_THROW(A.set_data(data2), InvalidMatrixFormat);
}

TEST(MatrixTest, TestTranspose)
{
    Matrix A(2, 3);

    std::vector<std::vector<double>> data = {{1, 2, 3}, {4, 5, 6}};
    A.set_data(data);

    Matrix B = A.transpose();

    for (int i = 0; i < B.get_rows(); i++)
    {
        for (int j = 0; j < B.get_cols(); j++)
        {
            EXPECT_EQ(B.get_element(i, j), data[j][i]);
        }
    }
}
