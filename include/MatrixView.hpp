
/**
 * @class MatrixView
 * @brief Provides a view into a matrix
 *
 * This class provides a view into a matrix so that operations can be performed without having
 * to allocate new memory.
 *
 * Example usage:
 * @code
 * MatrixView transpose = matrix.transpose();
 * @endcode
 *
 * This will return a view so that new memory don't have to be allocated to transpose matrix.
 *
 */
class MatrixView
{
public:
    const double *parent_data;
    int rows, cols;
    int row_offset, col_offset;

    /**
     * @brief Constructs a MatrixView object that provides a view into a parent matrix.
     *
     * @param data A pointer to the parent matrix's data.
     * @param r The number of rows in the view.
     * @param c The number of columns in the view.
     * @param row_off The row offset from the parent matrix's origin.
     * @param col_off The column offset from the parent matrix's origin.
     */
    MatrixView(const double *data, int r, int c, int row_off, int col_off);

    /**
     * @brief Returns the element at the specified row and column in the view.
     *
     * This function retrieves the element at the given row and column in the view,
     * considering the row and column offsets of the parent matrix.
     *
     * @param row The row index of the element to retrieve.
     * @param col The column index of the element to retrieve.
     *
     * @return The value of the element at the specified row and column in the view.
     */
    double get_element(int row, int col) const;
    int get_rows() const;
    int get_cols() const;
};