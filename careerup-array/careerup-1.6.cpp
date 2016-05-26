#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE rotate

#include <boost/test/unit_test.hpp>

template <size_t size>
void
rotate(int image[][size]);

BOOST_AUTO_TEST_CASE(rotate_image)
{
    const int n = 10;
    int test_img[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            test_img[i][j] = i + 1;
        }
    }
    int result_img[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result_img[i][j] = n - j;
        }
    }
    rotate(test_img);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            BOOST_CHECK_EQUAL(test_img[i][j], result_img[i][j]);
        }
    }
}

template <size_t size>
void
rotate(int image[][size])
{
    for (int wall = 0; wall < size / 2; wall++) {
        int first = wall;
        int last = size - 1 - wall;
        for (int i = first; i < last; i++) {
            int offset = i - first;
            int temp = image[first][i];
            image[first][i] = image[last - offset][wall];
            image[last - offset][wall] = image[last][last - offset];
            image[last][last - offset] = image[i][last];
            image[i][last] = temp;
        }
    }
}

