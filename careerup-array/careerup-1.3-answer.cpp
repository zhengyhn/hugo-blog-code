#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE remove_duplicate

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <boost/test/unit_test.hpp>

void
rm_dup(char *str);

BOOST_AUTO_TEST_CASE(null)
{
    rm_dup(NULL);
}

BOOST_AUTO_TEST_CASE(No_duplicate)
{
    char test_str[] = "abcd";
    rm_dup(test_str);
    BOOST_CHECK_EQUAL(test_str, "abcd");
}

BOOST_AUTO_TEST_CASE(All_duplicate)
{
    char test_str[] = "aaaa";
    rm_dup(test_str);
    BOOST_CHECK_EQUAL(test_str, "a");
}

BOOST_AUTO_TEST_CASE(Empty)
{
    char test_str[] = "";
    rm_dup(test_str);
    BOOST_CHECK_EQUAL(test_str, "");
}

BOOST_AUTO_TEST_CASE(Continual_duplicate)
{
    char test_str[] = "aaabbb";
    rm_dup(test_str);
    BOOST_CHECK_EQUAL(test_str, "ab");
}

BOOST_AUTO_TEST_CASE(Non_continual_duplicate)
{
    char test_str[] = "abababa";
    rm_dup(test_str);
    BOOST_CHECK_EQUAL(test_str, "ab");
}

BOOST_AUTO_TEST_CASE(random_string)
{
    char test_str6[20];    
    srand(time(0));
    for (int i = 0; i < 20; ++i) {
        test_str6[i] = 'a' + rand() % 26;
    }
    std::cout << test_str6 << std::endl;
    rm_dup(test_str6);
    std::cout << test_str6 << std::endl;
}

void
rm_dup(char *str)
{
    if (str == NULL) {
        return;
    }

    int tail = 1;
    for (int i = 1; i < strlen(str); ++i) {
        int j;
        for (j = 0; j < tail; ++j) {
            if (str[i] == str[j]) {
                break;
            }
        }
        if (j == tail) {
            str[tail] = str[i];
            tail++;
        }
    }
    str[tail] = '\0';
}

