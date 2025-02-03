#include <gtest/gtest.h>

#include "../include/Matrix.hpp"
#include "../include/InvalidMatrixFormat.hpp"
#include "../include/TransposedMatrixView.hpp"

#include <iostream>

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

TEST(MatrixTest, SetDataNonSquare)
{
    Matrix A(2, 3);

    std::vector<std::vector<double>> data = {{1, 2, 3}, {4, 5, 6}};

    A.set_data(data);

    for (int i = 0; i < A.get_rows(); i++)
    {
        for (int j = 0; j < A.get_cols(); j++)
        {
            EXPECT_EQ(A.get_element(i, j), data[i][j]);
        }
    }
}

TEST(MatrixTest, TestIndexingOperator)
{
    Matrix A(2, 2);
    A(0, 0) = 17.23;

    EXPECT_EQ(A.get_element(0, 0), 17.23);
    EXPECT_EQ(A(0, 0), 17.23);
}

TEST(MatrixTest, IndexingOperatorThrowsFormatException)
{
    Matrix A(2, 2);

    EXPECT_THROW(A(2, 2), std::out_of_range);
    EXPECT_THROW(A(-1, 0), std::out_of_range);
    EXPECT_THROW(A(0, -1), std::out_of_range);
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
            EXPECT_EQ(B(i, j), data[j][i]);
        }
    }
}

TEST(MatrixTest, TestViewTranspose)
{
    Matrix A(2, 3);

    std::vector<std::vector<double>> data = {{1, 2, 3}, {4, 5, 6}};
    A.set_data(data);

    TransposedMatrixView A_transpose_view = A.transpose_view();

    for (int i = 0; i < A_transpose_view.get_rows(); i++)
    {
        for (int j = 0; j < A_transpose_view.get_cols(); j++)
        {
            EXPECT_EQ(A_transpose_view.get_element(i, j), data[j][i]);
        }
    }
}

TEST(MatrixTest, TestCreateSquareViewHasCorrectData)
{
    Matrix A(2, 3);

    std::vector<std::vector<double>> data = {{1, 2, 3}, {4, 5, 6}};
    A.set_data(data);

    PaddedMatrixView A_square_view = A.create_square_view();

    for (int i = 0; i < A_square_view.get_rows(); i++)
    {
        for (int j = 0; j < A_square_view.get_cols(); j++)
        {
            if (i < data.size() && j < data[i].size())
            {
                EXPECT_EQ(A_square_view.get_element(i, j), data[i][j]);
            }
            else
            {
                EXPECT_EQ(A_square_view.get_element(i, j), 0);
            }
        }
    }
}

TEST(MatrixTest, TestCreateSquareViewHasCorrectShape)
{
    Matrix A(15, 23);
    Matrix B(42, 42);
    Matrix C(8, 8);
    Matrix D(23, 15);

    PaddedMatrixView A_square_view = A.create_square_view();
    PaddedMatrixView B_square_view = B.create_square_view();
    PaddedMatrixView C_square_view = C.create_square_view();
    PaddedMatrixView D_square_view = D.create_square_view();

    EXPECT_EQ(A_square_view.get_rows(), 32);
    EXPECT_EQ(A_square_view.get_cols(), 32);

    EXPECT_EQ(B_square_view.get_rows(), 64);
    EXPECT_EQ(B_square_view.get_cols(), 64);

    EXPECT_EQ(C_square_view.get_rows(), 8);
    EXPECT_EQ(C_square_view.get_cols(), 8);

    EXPECT_EQ(D_square_view.get_rows(), 32);
    EXPECT_EQ(D_square_view.get_cols(), 32);
}

TEST(MatrixTest, TestAdditionOperatorPositiveNumbers)
{
    Matrix A(2, 2);
    Matrix B(2, 2);

    std::vector<std::vector<double>> AData = {{1, 2}, {3, 4}};
    std::vector<std::vector<double>> BData = {{5, 6}, {7, 8}};

    A.set_data(AData);
    B.set_data(BData);

    Matrix C = A + B;

    std::vector<std::vector<double>> expected_data = {{1 + 5, 2 + 6}, {3 + 7, 4 + 8}};

    for (int i = 0; i < C.get_rows(); i++)
    {
        for (int j = 0; j < C.get_cols(); j++)
        {
            EXPECT_EQ(C.get_element(i, j), expected_data[i][j]);
        }
    }
}

TEST(MatrixTest, TestAdditionOperatorNegativeNumbers)
{
    Matrix A(2, 2);
    Matrix B(2, 2);

    std::vector<std::vector<double>> AData = {{1, 2}, {3, 4}};
    std::vector<std::vector<double>> BData = {{-5, -6}, {-7, -8}};

    A.set_data(AData);
    B.set_data(BData);

    Matrix C = A + B;

    std::vector<std::vector<double>> expected_data = {{-4, -4}, {-4, -4}};

    for (int i = 0; i < C.get_rows(); i++)
    {
        for (int j = 0; j < C.get_cols(); j++)
        {
            EXPECT_EQ(C.get_element(i, j), expected_data[i][j]);
        }
    }
}

TEST(MatrixTest, TestSubtractionOperatorPositiveNumbers)
{
    Matrix A(2, 2);
    Matrix B(2, 2);

    std::vector<std::vector<double>> AData = {{1, 2}, {3, 4}};
    std::vector<std::vector<double>> BData = {{5, 6}, {7, 8}};

    A.set_data(AData);
    B.set_data(BData);

    Matrix C = A - B;

    std::vector<std::vector<double>> expected_data = {{-4, -4}, {-4, -4}};

    for (int i = 0; i < C.get_rows(); i++)
    {
        for (int j = 0; j < C.get_cols(); j++)
        {
            EXPECT_EQ(C.get_element(i, j), expected_data[i][j]);
        }
    }
}

TEST(MatrixTest, TestSubtractionOperatorNegativeNumbers)
{
    Matrix A(2, 2);
    Matrix B(2, 2);

    std::vector<std::vector<double>> AData = {{1, 2}, {3, 4}};
    std::vector<std::vector<double>> BData = {{-5, -6}, {-7, -8}};

    A.set_data(AData);
    B.set_data(BData);

    Matrix C = A - B;

    std::vector<std::vector<double>> expected_data = {{6, 8}, {10, 12}};

    for (int i = 0; i < C.get_rows(); i++)
    {
        for (int j = 0; j < C.get_cols(); j++)
        {
            EXPECT_EQ(C.get_element(i, j), expected_data[i][j]);
        }
    }
}

TEST(MatrixViewTest, TestConvertToMatrix)
{
    // TODO: Test convert_to_matrix() method
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
