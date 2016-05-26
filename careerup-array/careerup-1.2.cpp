#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE reverse_string

#include <boost/test/unit_test.hpp>
#include <iostream>

char *
reverse_str(char *str);

BOOST_AUTO_TEST_CASE(reverse_string)
{
    char test_str[] = "abcd";
    BOOST_CHECK_EQUAL(reverse_str(test_str), "dcba");
}

char *
reverse_str(char *str)
{
    if (str == NULL) {
        return str;
    }

    int len = 0;

    while (*(str + len)) {
        ++len;
    }

    for (int i = 0; i < len / 2; ++i) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }

    return str;
}
