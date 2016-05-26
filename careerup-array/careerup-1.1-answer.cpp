#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE has_unique

#include <boost/test/unit_test.hpp>
#include <iostream>

bool
has_unique_char_array(const std::string& str);

bool
has_unique_char_bit(const std::string& str);

BOOST_AUTO_TEST_CASE(has_unique)
{
    const std::string test_str1 = "abcd";
    const std::string test_str2 = "abca";

    BOOST_CHECK(has_unique_char_array(test_str1));
    BOOST_CHECK(has_unique_char_array(test_str2));
    BOOST_CHECK(has_unique_char_bit(test_str1));
    BOOST_CHECK(has_unique_char_bit(test_str2));
}

bool
has_unique_char_array(const std::string& str)
{
    bool has_char[256] = {false};

    for (int i = 0; i < str.length(); ++i) {
        if (has_char[str[i]]) {
            return false;
        } else {
            has_char[str[i]] = true;
        }
    }
    return true;
}

bool
has_unique_char_bit(const std::string& str)
{
    int char_flag = 0;

    for (int i = 0; i < str.length(); ++i) {
        if ((char_flag & (0x1 << (str[i] - 'a'))) == 0) {
            char_flag |= 0x1 << (str[i] - 'a');
        } else {
            return false;
        }
    }
    return true;
}
