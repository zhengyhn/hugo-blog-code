#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE has_unique

#include <boost/test/unit_test.hpp>
#include <tr1/unordered_set>
#include <iostream>

bool
has_unique_char_normal(const std::string& str);

bool
has_unique_char_set(const std::string& str);

BOOST_AUTO_TEST_CASE(has_unique)
{
    const std::string test_str1 = "abcd";
    const std::string test_str2 = "abca";

    BOOST_CHECK(has_unique_char_normal(test_str1));
    BOOST_CHECK(has_unique_char_normal(test_str2));
    BOOST_CHECK(has_unique_char_set(test_str1));
    BOOST_CHECK(has_unique_char_set(test_str2));
}

bool
has_unique_char_normal(const std::string& str)
{
    for (int i = 0; i < str.length(); ++i) {
        for (int j = i + 1; j < str.length(); ++j) {
            if (str[i] == str[j]) {
                return false;
            }
        }
    }
    return true;
}

bool
has_unique_char_set(const std::string& str)
{
    typedef std::tr1::unordered_set<char> Set;
    Set set;
    
    for (int i = 0; i < str.length(); ++i) {
        if (set.count(str[i]) == 0) {
            set.insert(str[i]);
        } else {
            return false;
        }
    }
    return true;
}
