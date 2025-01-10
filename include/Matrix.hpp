#pragma once

#include "../include/MatrixView.hpp"
#include "../include/TransposedMatrixView.hpp"
#include "../include/PaddedMatrixView.hpp"

#include <vector>

// Forward declaration of MatrixView
class MatrixView;

/**
 * @class Matrix
 * @brief Represents a matrix of double values.
 *
 * This class represents a matrix of double values and provides basic operations on matrices.
 *
 * Example usage:
 * @code
 * Matrix m(2, 3);
 * m.set_element(0, 0, 1.0);
 * m.set_element(0, 1, 2.0);
 * m.set_element(0, 2, 3.0);
 * m.set_element(1, 0, 4.0);
 * m.set_element(1, 1, 5.0);
 * m.set_element(1, 2, 6.0);
 * @endcode
 *
 * This will create a 2x3 matrix and set its elements to the values provided.
 */
class Matrix
{
public:
    /**
     * @brief Constructs a Matrix object with the specified number of rows and columns.
     *
     * Initializes the matrix with zeros.
     *
     * @param r The number of rows in the matrix.
     * @param c The number of columns in the matrix.
     */
    Matrix(int r, int c);

    /**
     * @brief Transposes the current matrix.
     *
     * This function creates a new matrix where the rows and columns are swapped.
     * The original matrix remains unchanged.
     *
     * @return A new matrix that is the transpose of the current matrix.
     */
    Matrix transpose() const;

    /**
     * @brief Returns a view of the transposed matrix.
     *
     * This function creates and returns a MatrixView object that represents the transposed version of the current matrix.
     * The MatrixView object shares the same underlying data with the original matrix, but with dimensions swapped.
     *
     * @return A MatrixView object representing the transposed matrix.
     *
     * @note The returned MatrixView object does not own the underlying data and should not be used to modify the original matrix.
     *
     * @see MatrixView
     */
    TransposedMatrixView transpose_view() const;

    /**
     * @brief Creates a square view of the current matrix.
     *
     * If the number of rows is less than the number of columns, the function adds rows to the matrix
     * until the number of rows equals the number of columns. Then, it finds the smallest integer power of two
     * that is greater than or equal to the number of columns. The resulting integer is used to create a square view
     * of the matrix.
     *
     * @return A MatrixView object representing a square view of the current matrix.
     *
     * @note This function should not be used in production code. It is only intended for testing and debugging purposes.
     */
    PaddedMatrixView create_square_view() const;

    /**
     * @brief This method is for testing purposes only and should not be used in production.
     *
     * Use set_element() to set data in the matrix.
     */
    void set_data(const std::vector<std::vector<double>> &newData);

    /**
     * @brief Overloads the subscript operator to access elements in the matrix.
     *
     * @param row The row index of the element to access.
     * @param col The column index of the element to access.
     *
     * @return The value of the element at the specified column and row.
     *
     * @throws std::out_of_range If the specified column or row index is out of bounds.
     */
    double &operator()(int row, int col);

    /**
     * @brief Overloads the subscript operator to access elements in the matrix.
     *
     * @param row The row index of the element to access.
     * @param col The column index of the element to access.
     *
     * @return The value of the element at the specified column and row.
     *
     * @throws std::out_of_range If the specified column or row index is out of bounds.
     */
    const double &operator()(int row, int col) const;

    /**
     * @brief Overloads the addition operator. Adds two matrices element-wise and returns a new matrix.
     *
     * @param other The other matrix to add to the current matrix.
     */
    Matrix operator+(const Matrix &other) const;

    /**
     * @brief Overloads the subtraction operator. Adds two matrices element-wise and returns a new matrix.
     *
     * @param other The other matrix to add to the current matrix.
     */
    Matrix operator-(const Matrix &other) const;

    /**
     *  @brief Overloads the multiplication operator to multiply a matrix by a scalar.
     *
     * @param scalar The scalar to multiply with, have to be convertible to double.
     */
    template <typename T>
    Matrix operator*(const T scalar) const
    {

        static_assert(std::is_convertible<T, double>::value,
                      "Scalar type must be convertible to double.");

        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result(i, j) = get_element(i, j) * static_cast<double>(scalar);
            }
        }
    }

    /**
     * @brief Sets the value of an element in the matrix at the specified column and row.
     *
     * @param col The column index of the element to set.
     * @param row The row index of the element to set.
     * @param val The new value to assign to the element.
     *
     * @throws std::out_of_range If the specified column or row index is out of bounds.
     */
    void set_element(int row, int col, double val);

    /**
     * @brief Retrieves the value of an element in the matrix at the specified column and row.
     *
     * @param col The column index of the element to retrieve.
     * @param row The row index of the element to retrieve.
     *
     * @return The value of the element at the specified column and row.
     *
     * @throws std::out_of_range If the specified column or row index is out of bounds.
     */
    double get_element(int row, int col) const;

    void display() const;
    int get_rows() const;
    int get_cols() const;

private:
    int rows, cols;
    std::shared_ptr<double[]> data;

    bool is_valid_index(int row, int col) const;

    friend class MatrixView;
};