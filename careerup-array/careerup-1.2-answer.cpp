#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE reverse_string

#include <boost/test/unit_test.hpp>
#include <iostream>

void
reverse(char *str);

BOOST_AUTO_TEST_CASE(reverse_string)
{
    char test_str[] = "abcd";
    reverse(test_str);
    BOOST_CHECK_EQUAL(test_str, "dcba");
}

void
reverse(char *str)
{
    char *end = str;
    char tmp;
    
    if (str) {
        while (*end) {
            ++end;
        }
        --end;
        while (str < end) {
            tmp = *str;
            *str++ = *end;
            *end-- = tmp;
        }
    }
}
