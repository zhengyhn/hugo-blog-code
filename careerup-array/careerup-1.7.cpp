#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE matrix

#include <boost/test/unit_test.hpp>

template <size_t row, size_t col>
void
clear(int (&matrix)[row][col]);

BOOST_AUTO_TEST_CASE(normal)
{
    const size_t m = 4;
    const size_t n = 5;
    int test_matrix[m][n] = {{1, 1, 1, 1, 1},
                             {1, 0, 1, 1, 1},
                             {1, 1, 1, 0, 1},
                             {1, 1, 1, 1, 1}};
    const int result_matrix[m][n] = {{1, 0, 1, 0, 1},
                                     {0, 0, 0, 0, 0},
                                     {0, 0, 0, 0, 0},
                                     {1, 0, 1, 0, 1}};
    clear(test_matrix);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            BOOST_CHECK_EQUAL(test_matrix[i][j], result_matrix[i][j]);
        }
    }
}

template <size_t row, size_t col>
void
clear(int (&matrix)[row][col])
{
    bool row_zero[row] = {false};
    bool col_zero[col] = {false};

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (matrix[i][j] == 0) {
                row_zero[i] = true;
                if (!col_zero[j]) {
                    col_zero[j] = true;
                }
                break;
            }
        }
    }
    for (int i = 0; i < row; ++i) {
        if (row_zero[i]) {
            for (int j = 0; j < col; ++j) {
                matrix[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < col; ++i) {
        if (col_zero[i]) {
            for (int j = 0; j < row; ++j) {
                matrix[j][i] = 0;
            }
        }
    }
}
