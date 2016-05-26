#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "bilist.hpp"

BOOST_AUTO_TEST_SUITE(test_create)

BOOST_AUTO_TEST_CASE(create_empty)
{
    BiLinkedList<int> list;
    BOOST_CHECK_EQUAL(list.size(), 0);

    int arr[5];
    BiLinkedList<int> list2(arr, 0);
    BOOST_CHECK_EQUAL(list2.size(), 0);
}

BOOST_AUTO_TEST_CASE(create_with_one_element)
{
    BiLinkedList<int> list_int(1);
    BOOST_CHECK_EQUAL(list_int.size(), 1);
    BOOST_CHECK_EQUAL(list_int[0], 1);

    BiLinkedList<char> list_char('a');
    BOOST_CHECK_EQUAL(list_char.size(), 1);
    BOOST_CHECK_EQUAL(list_char[0], 'a');

    BiLinkedList<double> list_double(1.23);
    BOOST_CHECK_EQUAL(list_double.size(), 1);
    BOOST_CHECK_EQUAL(list_double[0], 1.23);

    BiLinkedList<std::string> list_str("abc");
    BOOST_CHECK_EQUAL(list_str.size(), 1);
    BOOST_CHECK_EQUAL(list_str[0], "abc");
}

BOOST_AUTO_TEST_CASE(create_with_an_array)
{
    int arr[5] = {1, 2, 3, 4, 5};
    BiLinkedList<int> list(arr, 5);
    boost::test_tools::output_test_stream output;
    output << list;
    BOOST_CHECK(output.is_equal("[1, 2, 3, 4, 5]"));
}

BOOST_AUTO_TEST_CASE(create_copy_empty)
{
    BiLinkedList<int> *list1 = new BiLinkedList<int>();
    BiLinkedList<int> list2(*list1);
    delete list1;
    BOOST_CHECK_EQUAL(list2.size(), 0);
}

BOOST_AUTO_TEST_CASE(create_copy_one)
{
    BiLinkedList<int> *list1 = new BiLinkedList<int>(3);
    BiLinkedList<int> list2(*list1);
    delete list1;
    BOOST_CHECK_EQUAL(list2.size(), 1);
    BOOST_CHECK_EQUAL(list2[0], 3);
}

BOOST_AUTO_TEST_CASE(create_and_assign)
{
    int arr[3] = {1, 2, 3};
    BiLinkedList<int> list1(arr, 3);

    int a[2] = {4, 5};
    BiLinkedList<int> list2(a, 2);

    list1 = list2;
    list1 = list1;

    BOOST_CHECK_EQUAL(list1.size(), 2);
    boost::test_tools::output_test_stream output;
    output << list1;
    BOOST_CHECK(output.is_equal("[4, 5]"));
}

BOOST_AUTO_TEST_CASE(assign_empty)
{
    BiLinkedList<int> list1(2);
    BiLinkedList<int> list2;
    list1 = list2;
    BOOST_CHECK_EQUAL(list1.size(), 0);
    list1 = list1;
    BOOST_CHECK_EQUAL(list1.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_output)

BOOST_AUTO_TEST_CASE(ouput_empty)
{
    BiLinkedList<int> list;
    boost::test_tools::output_test_stream output;
    output << list;
    BOOST_CHECK(output.is_equal("[]"));
}

BOOST_AUTO_TEST_CASE(output_one)
{
    BiLinkedList<int> list(2);
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
    BiLinkedList<int> list;

    list.append(1);

    boost::test_tools::output_test_stream out;
    out << list;
    BOOST_CHECK(out.is_equal("[1]"));
    BOOST_CHECK_EQUAL(list.size(), 1);
}

BOOST_AUTO_TEST_CASE(append_to_normal)
{
    int arr[5] = {1, 1, 1, 1, 1};
    BiLinkedList<int> list(arr, 5);

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
    BiLinkedList<int> list;
    list.insert(0, 1);
    BOOST_CHECK_EQUAL(list.size(), 1);
    BOOST_CHECK_EQUAL(list[0], 1);
}

BOOST_AUTO_TEST_CASE(insert_bound)
{
    BiLinkedList<int> list(2);
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
    BiLinkedList<int> list;
    list.remove(0);
    BOOST_CHECK_EQUAL(list.size(), 0);
}

BOOST_AUTO_TEST_CASE(remove_bound)
{
    int arr[5] = {1, 2, 3, 4, 5};
    BiLinkedList<int> list(arr, 5);
    list.remove(0);
    list.remove(3);
    boost::test_tools::output_test_stream out;
    out << list;
    BOOST_CHECK(out.is_equal("[2, 3, 4]"));
    BOOST_CHECK_EQUAL(list.size(), 3);
}

BOOST_AUTO_TEST_CASE(remove_middle)
{
    BiLinkedList<int> list(3);
    list.append(2);
    list.append(1);
    list.remove(1);
    BOOST_CHECK_EQUAL(list[0], 3);
    BOOST_CHECK_EQUAL(list[1], 1);
}

BOOST_AUTO_TEST_SUITE_END()
