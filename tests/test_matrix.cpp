#include <gtest/gtest.h>

#include "../include/Matrix.hpp"
#include "../include/InvalidMatrixFormat.hpp"

TEST(MatrixTest, TestSetElement)
{
    Matrix A(2, 2);
    A.setElement(0, 0, 17.23);

    EXPECT_EQ(A.getElement(0, 0), 17.23);
}

TEST(MatrixTest, TestSetData)
{
    Matrix A(2, 2);

    std::vector<std::vector<double>> data = {{1, 2}, {3, 4}};
    A.setData(data);

    for (int i = 0; i < A.getRows(); i++)
    {
        for (int j = 0; j < A.getCols(); j++)
        {
            EXPECT_EQ(A.getElement(i, j), data[i][j]);
        }
    }
}

TEST(MatrixTest, TestSetElementThrowsFormatException)
{
    Matrix A(2, 2);

    std::vector<std::vector<double>> data1 = {{1, 2}, {3, 4}, {5, 6}};
    std::vector<std::vector<double>> data2 = {{1, 2, 3}, {4, 5, 6}};

    EXPECT_THROW(A.setData(data1), InvalidMatrixFormat);
    EXPECT_THROW(A.setData(data2), InvalidMatrixFormat);
}

TEST(MatrixTest, TestTranspose)
{
    Matrix A(2, 3);

    std::vector<std::vector<double>> data = {{1, 2, 3}, {4, 5, 6}};
    A.setData(data);

    Matrix B = A.transpose();

    for (int i = 0; i < B.getRows(); i++)
    {
        for (int j = 0; j < B.getCols(); j++)
        {
            EXPECT_EQ(B.getElement(i, j), data[j][i]);
        }
    }
}
