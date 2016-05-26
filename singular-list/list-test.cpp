#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_SUITE(test_create)

BOOST_AUTO_TEST_CASE(create_empty)
{
    LinkedList<int> list;
    BOOST_CHECK_EQUAL(list.size(), 0);

    int arr[5];
    LinkedList<int> list2(arr, 0);
    BOOST_CHECK_EQUAL(list2.size(), 0);
}

BOOST_AUTO_TEST_CASE(create_with_one_element)
{
    LinkedList<int> list_int(1);
    BOOST_CHECK_EQUAL(list_int.size(), 1);
    BOOST_CHECK_EQUAL(list_int[0], 1);

    LinkedList<char> list_char('a');
    BOOST_CHECK_EQUAL(list_char.size(), 1);
    BOOST_CHECK_EQUAL(list_char[0], 'a');

    LinkedList<double> list_double(1.23);
    BOOST_CHECK_EQUAL(list_double.size(), 1);
    BOOST_CHECK_EQUAL(list_double[0], 1.23);

    LinkedList<std::string> list_str("abc");
    BOOST_CHECK_EQUAL(list_str.size(), 1);
    BOOST_CHECK_EQUAL(list_str[0], "abc");
}

BOOST_AUTO_TEST_CASE(create_with_an_array)
{
    int arr[5] = {1, 2, 3, 4, 5};
    LinkedList<int> list(arr, 5);
    boost::test_tools::output_test_stream output;
    output << list;
    BOOST_CHECK(output.is_equal("[1, 2, 3, 4, 5]"));
}

BOOST_AUTO_TEST_CASE(create_copy_empty)
{
    LinkedList<int> *list1 = new LinkedList<int>();
    LinkedList<int> list2(*list1);
    delete list1;
    BOOST_CHECK_EQUAL(list2.size(), 0);
}

BOOST_AUTO_TEST_CASE(create_copy_one)
{
    LinkedList<int> *list1 = new LinkedList<int>(3);
    LinkedList<int> list2(*list1);
    delete list1;
    BOOST_CHECK_EQUAL(list2.size(), 1);
    BOOST_CHECK_EQUAL(list2[0], 3);
}

BOOST_AUTO_TEST_CASE(create_and_assign)
{
    int arr[3] = {1, 2, 3};
    LinkedList<int> list1(arr, 3);

    int a[2] = {4, 5};
    LinkedList<int> list2(a, 2);

    list1 = list2;
    list1 = list1;

    BOOST_CHECK_EQUAL(list1.size(), 2);
    boost::test_tools::output_test_stream output;
    output << list1;
    BOOST_CHECK(output.is_equal("[4, 5]"));
}

BOOST_AUTO_TEST_CASE(assign_empty)
{
    LinkedList<int> list1(2);
    LinkedList<int> list2;
    list1 = list2;
    BOOST_CHECK_EQUAL(list1.size(), 0);
    list1 = list1;
    BOOST_CHECK_EQUAL(list1.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_output)

BOOST_AUTO_TEST_CASE(ouput_empty)
{
    LinkedList<int> list;
    boost::test_tools::output_test_stream output;
    output << list;
    BOOST_CHECK(output.is_equal("[]"));
}

BOOST_AUTO_TEST_CASE(output_one)
{
    LinkedList<int> list(2);
    boost::test_tools::output_test_stream output;
    output << list;
    BOOST_CHECK(output.is_equal("[2]"));
    
    output << list[0];
    BOOST_CHECK(output.is_equal("2"));
}

BOOST_AUTO_TEST_SUITE_END()
  
BOOST_AUTO_TEST_SUITE(test_append)

BOOST_AUTO_TEST_CASE(append_to_empty)
{
    LinkedList<int> list;

    list.append(1);

    boost::test_tools::output_test_stream out;
    out << list;
    BOOST_CHECK(out.is_equal("[1]"));
    BOOST_CHECK_EQUAL(list.size(), 1);
}

BOOST_AUTO_TEST_CASE(append_to_normal)
{
    int arr[5] = {1, 1, 1, 1, 1};
    LinkedList<int> list(arr, 5);

    list.append(2);

    boost::test_tools::output_test_stream out;
    out << list;
    BOOST_CHECK(out.is_equal("[1, 1, 1, 1, 1, 2]"));
    BOOST_CHECK_EQUAL(list.size(), 6);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_insert)

BOOST_AUTO_TEST_CASE(insert_empty)
{
    LinkedList<int> list;
    list.insert(0, 1);
    BOOST_CHECK_EQUAL(list.size(), 1);
    BOOST_CHECK_EQUAL(list[0], 1);
}

BOOST_AUTO_TEST_CASE(insert_bound)
{
    LinkedList<int> list(2);
    list.insert(0, 0);
    list.insert(1, 1);
    list.insert(3, 3);
    boost::test_tools::output_test_stream out;
    out << list;
    BOOST_CHECK_EQUAL(list.size(), 4);
    BOOST_CHECK(out.is_equal("[0, 1, 2, 3]"));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_remove)

BOOST_AUTO_TEST_CASE(remove_empty)
{
    LinkedList<int> list;
    list.remove(0);
    BOOST_CHECK_EQUAL(list.size(), 0);
}

BOOST_AUTO_TEST_CASE(remove_bound)
{
    int arr[5] = {1, 2, 3, 4, 5};
    LinkedList<int> list(arr, 5);
    list.remove(0);
    list.remove(3);
    boost::test_tools::output_test_stream out;
    out << list;
    BOOST_CHECK(out.is_equal("[2, 3, 4]"));
    BOOST_CHECK_EQUAL(list.size(), 3);
}

BOOST_AUTO_TEST_CASE(remove_middle)
{
    LinkedList<int> list(3);
    list.append(2);
    list.append(1);
    list.remove(1);
    BOOST_CHECK_EQUAL(list[0], 3);
    BOOST_CHECK_EQUAL(list[1], 1);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_reverse)

BOOST_AUTO_TEST_CASE(reverse_empty)
{
    LinkedList<int> list;
    list.reverse();
    BOOST_CHECK_EQUAL(list.size(), 0);
}

BOOST_AUTO_TEST_CASE(reverse_one)
{
    LinkedList<int> list(2);
    list.reverse();
    BOOST_CHECK_EQUAL(list[0], 2);
}

BOOST_AUTO_TEST_CASE(reverse_short)
{
    char a[5] = {'a', 'b', 'c', 'd', 'e'};
    LinkedList<char> list(a, 5);
    list.reverse();
    boost::test_tools::output_test_stream out;
    out << list;
    BOOST_CHECK(out.is_equal("[e, d, c, b, a]"));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_sort)

BOOST_AUTO_TEST_CASE(sort_empty)
{
    LinkedList<int> list;
    list.sort();
    BOOST_CHECK_EQUAL(list.size(), 0);
}

BOOST_AUTO_TEST_CASE(sort_char)
{
    char c[10] = {'c', 'h', 'a', 'r', 'n', 'e', 'e', 'd', 't', 'o'};
    LinkedList<char> list(c, 10);
    list.sort();
    boost::test_tools::output_test_stream out;
    out << list;
    BOOST_CHECK(out.is_equal("[a, c, d, e, e, h, n, o, r, t]"));
}

BOOST_AUTO_TEST_CASE(sort_string)
{
    std::string str[10] = {"this", "is", "a", "string", "to", "test", "for",
                           "merge", "sort", "function"};
    LinkedList<std::string> list(str, 10);
    list.sort();
    boost::test_tools::output_test_stream out;
    out << list;
    BOOST_CHECK(out.is_equal("[a, for, function, is, merge, sort, string, \
test, this, to]"));
}

BOOST_AUTO_TEST_CASE(sort_sorted)
{
    int arr[5] = {1, 2, 3, 4, 5};
    LinkedList<int> list(arr, 5);
    list.sort();
    boost::test_tools::output_test_stream out;
    out << list;
    BOOST_CHECK(out.is_equal("[1, 2, 3, 4, 5]"));

    list.reverse();
    out << list;
    BOOST_CHECK(out.is_equal("[5, 4, 3, 2, 1]"));
    
    list.sort();
    out << list;
    BOOST_CHECK(out.is_equal("[1, 2, 3, 4, 5]"));
}

BOOST_AUTO_TEST_CASE(sort_one)
{
    LinkedList<int> list(2);
    list.sort();
    BOOST_CHECK_EQUAL(list[0], 2);
}

BOOST_AUTO_TEST_CASE(sort_two)
{
    int arr[2] = {2, 1};
    LinkedList<int> list(arr, 2);
    list.sort();
    BOOST_CHECK_EQUAL(list[0], 1);
    BOOST_CHECK_EQUAL(list[1], 2);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_remove_duplicate)

BOOST_AUTO_TEST_CASE(remove_empty)
{
    LinkedList<int> list;
    list.rm_dup();
    BOOST_CHECK_EQUAL(list.size(), 0);
}

BOOST_AUTO_TEST_CASE(remove_one_element_list)
{
    LinkedList<int> list(2);
    list.rm_dup();
    BOOST_CHECK_EQUAL(list.size(), 1);
    BOOST_CHECK_EQUAL(list[0], 2);
}

BOOST_AUTO_TEST_CASE(remove_all_duplicate)
{
    int arr[5] = {1, 1, 1, 1, 1};
    LinkedList<int> list(arr, 5);
    list.rm_dup();
    BOOST_CHECK_EQUAL(list.size(), 1);
    BOOST_CHECK_EQUAL(list[0], 1);
}

BOOST_AUTO_TEST_CASE(remove_one_duplicate)
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 2, 8, 9};
    LinkedList<int> list(arr, 10);
    list.rm_dup();
    BOOST_CHECK_EQUAL(list.size(), 9);
    boost::test_tools::output_test_stream out;
    out << list;
    BOOST_CHECK(out.is_equal("[1, 2, 3, 4, 5, 6, 7, 8, 9]"));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_nth_to_last)

int arr[5] = {1, 2, 3, 4, 5};
LinkedList<int> list(arr, 5);

BOOST_AUTO_TEST_CASE(last_but_not_least_one)
{
    BOOST_CHECK_EQUAL(list.nth_to_last(1), 4);
}

BOOST_AUTO_TEST_CASE(first_one)
{
    BOOST_CHECK_EQUAL(list.nth_to_last(4), 1);
}

BOOST_AUTO_TEST_CASE(normal)
{
    BOOST_CHECK_EQUAL(list.nth_to_last(2), 3);
}

BOOST_AUTO_TEST_SUITE_END()


