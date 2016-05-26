#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <iostream>

void
replace(std::string& str)
{
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == ' ') {
            str.replace(i, 1, "%20", 3);
            i += 2;
        }
    }
}

void
replace_fast(std::string& str)
{
    int num_space = 0;

    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == ' ') {
            ++num_space;
        }
    }
    int src = str.size() - 1;
    str.resize(str.size() + 2 * num_space);
    int dest = str.size() - 1;
    while (src >= 0) {
        if (str[src] == ' ') {
            str[dest] = '0';
            str[--dest] = '2';
            str[--dest] = '%';
        } else {
            str[dest] = str[src];
        }
        --src;
        --dest;
    }
}

BOOST_AUTO_TEST_CASE(normal)
{
    std::string test_str = "a b c";
    replace(test_str);
    BOOST_CHECK_EQUAL(test_str, "a%20b%20c");

    test_str = "a b c";
    replace_fast(test_str);
    BOOST_CHECK_EQUAL(test_str, "a%20b%20c");
}

BOOST_AUTO_TEST_CASE(bound)
{
    std::string test_str1 = " a b c ";
    std::string test_str2(test_str1);
    std::string result = "%20a%20b%20c%20";
    
    replace(test_str1);
    BOOST_CHECK_EQUAL(test_str1, result);

    replace_fast(test_str2);
    BOOST_CHECK_EQUAL(test_str2, result);
}

BOOST_AUTO_TEST_CASE(empty)
{
    std::string test_str1 = "";

    replace(test_str1);
    BOOST_CHECK_EQUAL(test_str1, test_str1);

    replace_fast(test_str1);
    BOOST_CHECK_EQUAL(test_str1, test_str1);
}

BOOST_AUTO_TEST_CASE(all_spaces)
{
    std::string str1 = "     ";
    std::string str2(str1);
    
    replace(str1);
    BOOST_CHECK_EQUAL(str1, "%20%20%20%20%20");

    replace(str2);
    BOOST_CHECK_EQUAL(str2, "%20%20%20%20%20");
}
