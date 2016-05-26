#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "cilist.hpp"

BOOST_AUTO_TEST_SUITE(test_create)

BOOST_AUTO_TEST_CASE(create_empty)
{
    CiLinkedList<int> list;
    BOOST_CHECK_EQUAL(list.size(), 0);

    int arr[5];
    CiLinkedList<int> list2(arr, 0);
    BOOST_CHECK_EQUAL(list2.size(), 0);
}

BOOST_AUTO_TEST_CASE(create_with_one_element)
{
    CiLinkedList<int> list_int(1);
    BOOST_CHECK_EQUAL(list_int.size(), 1);
    BOOST_CHECK_EQUAL(list_int[0], 1);

    CiLinkedList<char> list_char('a');
    BOOST_CHECK_EQUAL(list_char.size(), 1);
    BOOST_CHECK_EQUAL(list_char[0], 'a');

    CiLinkedList<double> list_double(1.23);
    BOOST_CHECK_EQUAL(list_double.size(), 1);
    BOOST_CHECK_EQUAL(list_double[0], 1.23);

    CiLinkedList<std::string> list_str("abc");
    BOOST_CHECK_EQUAL(list_str.size(), 1);
    BOOST_CHECK_EQUAL(list_str[0], "abc");
}

BOOST_AUTO_TEST_CASE(create_with_an_array)
{
    int arr[5] = {1, 2, 3, 4, 5};
    CiLinkedList<int> list(arr, 5);
    boost::test_tools::output_test_stream output;
    output << list;
    BOOST_CHECK(output.is_equal("[1, 2, 3, 4, 5]"));
}

BOOST_AUTO_TEST_CASE(create_copy_empty)
{
    CiLinkedList<int> *list1 = new CiLinkedList<int>();
    CiLinkedList<int> list2(*list1);
    delete list1;
    BOOST_CHECK_EQUAL(list2.size(), 0);
}

BOOST_AUTO_TEST_CASE(create_copy_one)
{
    CiLinkedList<int> *list1 = new CiLinkedList<int>(3);
    CiLinkedList<int> list2(*list1);
    delete list1;
    BOOST_CHECK_EQUAL(list2.size(), 1);
    BOOST_CHECK_EQUAL(list2[0], 3);
}

BOOST_AUTO_TEST_CASE(create_and_assign)
{
    int arr[3] = {1, 2, 3};
    CiLinkedList<int> list1(arr, 3);

    int a[2] = {4, 5};
    CiLinkedList<int> list2(a, 2);

    list1 = list2;
    list1 = list1;

    BOOST_CHECK_EQUAL(list1.size(), 2);
    boost::test_tools::output_test_stream output;
    output << list1;
    BOOST_CHECK(output.is_equal("[4, 5]"));
}

BOOST_AUTO_TEST_CASE(assign_empty)
{
    CiLinkedList<int> list1(2);
    CiLinkedList<int> list2;
    list1 = list2;
    BOOST_CHECK_EQUAL(list1.size(), 0);
    list1 = list1;
    BOOST_CHECK_EQUAL(list1.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_output)

BOOST_AUTO_TEST_CASE(ouput_empty)
{
    CiLinkedList<int> list;
    boost::test_tools::output_test_stream output;
    output << list;
    BOOST_CHECK(output.is_equal("[]"));
}

BOOST_AUTO_TEST_CASE(output_one)
{
    CiLinkedList<int> list(2);
    boost::test_tools::output_test_stream output;
    output << list;
    BOOST_CHECK(output.is_equal("[2]"));
    
    output << list[0];
    BOOST_CHECK(output.is_equal("2"));
}

BOOST_AUTO_TEST_SUITE_END()
  
BOOST_AUTO_TEST_SUITE(test_remove_duplicate)

BOOST_AUTO_TEST_CASE(remove_empty)
{
    CiLinkedList<int> list;
    list.rm_dup();
    BOOST_CHECK_EQUAL(list.size(), 0);
}

BOOST_AUTO_TEST_CASE(remove_one_element_list)
{
    CiLinkedList<int> list(2);
    list.rm_dup();
    BOOST_CHECK_EQUAL(list.size(), 1);
    BOOST_CHECK_EQUAL(list[0], 2);
}

BOOST_AUTO_TEST_CASE(remove_all_duplicate)
{
    int arr[5] = {1, 1, 1, 1, 1};
    CiLinkedList<int> list(arr, 5);
    list.rm_dup();
    BOOST_CHECK_EQUAL(list.size(), 1);
    BOOST_CHECK_EQUAL(list[0], 1);
}

BOOST_AUTO_TEST_CASE(remove_one_duplicate)
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 2, 8, 9};
    CiLinkedList<int> list(arr, 10);
    list.rm_dup();
    BOOST_CHECK_EQUAL(list.size(), 9);
    boost::test_tools::output_test_stream out;
    out << list;
    BOOST_CHECK(out.is_equal("[1, 2, 3, 4, 5, 6, 7, 8, 9]"));
}

BOOST_AUTO_TEST_CASE(circular_duplicate)
{
    int arr[10] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};
    CiLinkedList<int> list(arr, 10);
    list.rm_dup();
    BOOST_CHECK_EQUAL(list.size(), 5);
    boost::test_tools::output_test_stream out;
    out << list;
    BOOST_CHECK(out.is_equal("[1, 2, 3, 4, 5]"));
}

BOOST_AUTO_TEST_SUITE_END()



