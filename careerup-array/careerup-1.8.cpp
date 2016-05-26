#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE check_rotate

#include <boost/test/unit_test.hpp>
#include <iostream>

bool
is_rotate(const std::string str, const std::string rotate_str);

bool
is_substr(const std::string str, const std::string substr);

BOOST_AUTO_TEST_CASE(pass)
{
    const std::string str = "waterbottle";
    const std::string rotate_str = "erbottlewat";

    BOOST_CHECK(is_rotate(str, rotate_str));
}

bool
is_rotate(const std::string str, const std::string rotate_str)
{
    if (str.size() != rotate_str.size()) {
        return false;
    }
    const std::string new_str = str + str;
    if (is_substr(new_str, rotate_str)) {
        return true;
    } else {
        return false;
    }
}

bool
is_substr(const std::string str, const std::string substr)
{
    if (str.find(substr) == std::string::npos) {
        return false;
    }
    return true;
}

