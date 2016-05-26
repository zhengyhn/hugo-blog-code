#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE is_anagram

#include <iostream>
#include <boost/test/unit_test.hpp>

bool
is_anagram(const std::string& lhs, const std::string& rhs)
{
    int lhs_size = lhs.size();
    int rhs_size = rhs.size();

    if (lhs_size != rhs_size) {
        return false;
    }
    bool rhs_is_marked[rhs_size];
    memset(rhs_is_marked, false, rhs_size * sizeof(bool));
    for (int i = 0; i < lhs_size; ++i) {
        int j;
        for (j = 0; j < rhs_size; ++j) {
            if (rhs_is_marked[j]) {
                continue;
            } else if (lhs[i] == rhs[j]) {
                rhs_is_marked[j] = true;
                break;
            }
        }
        if (j == rhs_size) {
            return false;
        }
    }
    return true;
}
        
BOOST_AUTO_TEST_CASE(test_is_anagram)
{
    BOOST_CHECK(is_anagram("abc", "abcd"));
    BOOST_CHECK(is_anagram("abc", "cab"));
    BOOST_CHECK(is_anagram("orchestra", "carthorse"));
}
