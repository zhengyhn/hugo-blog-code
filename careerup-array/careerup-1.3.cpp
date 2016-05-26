#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE remove_duplicate

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <boost/test/unit_test.hpp>

void
rm_dup(char *str);

BOOST_AUTO_TEST_CASE(remove_duplicate)
{
    char test_str[20];

    srand(time(0));
    for (int i = 0; i < 20; ++i) {
        test_str[i] = 'a' + rand() % 26;
    }
    std::cout << test_str << std::endl;
    rm_dup(test_str);
    std::cout << test_str << std::endl;
}

void
rm_dup(char *str)
{
    for (int i = 1; i < strlen(str); ++i) {
        int j;
        for (j = 0; j < i; ++j) {
            if (str[i] == str[j]) {
                break;
            }
        }
        if (j < i) {
            for (int k = i; k < strlen(str); ++k) {
                str[k] = str[k + 1];
            }
            --i;
        }
    }
}

