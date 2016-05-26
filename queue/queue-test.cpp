#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "queue.hpp"

BOOST_AUTO_TEST_SUITE(test_create)

BOOST_AUTO_TEST_CASE(create_empty)
{
    Queue<int> queue;
    BOOST_CHECK_EQUAL(queue.size(), 0);

    int arr[5];
    Queue<int> queue2(arr, 0);
    BOOST_CHECK_EQUAL(queue2.size(), 0);
}

BOOST_AUTO_TEST_CASE(create_with_one_element)
{
    Queue<int> queue_int(1);
    BOOST_CHECK_EQUAL(queue_int.size(), 1);
    BOOST_CHECK_EQUAL(queue_int.head(), 1);

    Queue<char> queue_char('a');
    BOOST_CHECK_EQUAL(queue_char.size(), 1);
    BOOST_CHECK_EQUAL(queue_char.head(), 'a');

    Queue<double> queue_double(1.23);
    BOOST_CHECK_EQUAL(queue_double.size(), 1);
    BOOST_CHECK_EQUAL(queue_double.head(), 1.23);

    Queue<std::string> queue_str("abc");
    BOOST_CHECK_EQUAL(queue_str.size(), 1);
    BOOST_CHECK_EQUAL(queue_str.head(), "abc");
}

BOOST_AUTO_TEST_CASE(create_with_an_array)
{
    int arr[5] = {1, 2, 3, 4, 5};
    Queue<int> queue(arr, 5);
    boost::test_tools::output_test_stream output;
    output << queue;
    BOOST_CHECK(output.is_equal("[1 | 2 | 3 | 4 | 5]"));
}

BOOST_AUTO_TEST_CASE(create_copy_empty)
{
    Queue<int> *queue1 = new Queue<int>();
    Queue<int> queue2(*queue1);
    delete queue1;
    BOOST_CHECK_EQUAL(queue2.size(), 0);
}

BOOST_AUTO_TEST_CASE(create_copy_one)
{
    Queue<int> *queue1 = new Queue<int>(3);
    Queue<int> queue2(*queue1);
    delete queue1;
    BOOST_CHECK_EQUAL(queue2.size(), 1);
    BOOST_CHECK_EQUAL(queue2.head(), 3);
}

BOOST_AUTO_TEST_CASE(create_and_assign)
{
    int arr[3] = {1, 2, 3};
    Queue<int> queue1(arr, 3);

    int a[2] = {4, 5};
    Queue<int> queue2(a, 2);

    queue1 = queue2;
    boost::test_tools::output_test_stream output;
    output << queue1;
    BOOST_CHECK(output.is_equal("[4 | 5]"));

    queue1 = queue1;
    BOOST_CHECK_EQUAL(queue1.size(), 2);
    output << queue1;
    BOOST_CHECK(output.is_equal("[4 | 5]"));
}

BOOST_AUTO_TEST_CASE(assign_empty)
{
    Queue<int> queue1(2);
    Queue<int> queue2;
    queue1 = queue2;
    BOOST_CHECK_EQUAL(queue1.size(), 0);
    queue1 = queue1;
    BOOST_CHECK_EQUAL(queue1.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_output)

BOOST_AUTO_TEST_CASE(ouput_empty)
{
    Queue<int> queue;
    boost::test_tools::output_test_stream output;
    output << queue;
    BOOST_CHECK(output.is_equal("[]"));
}

BOOST_AUTO_TEST_CASE(output_one)
{
    Queue<int> queue(2);
    boost::test_tools::output_test_stream output;
    output << queue;
    BOOST_CHECK(output.is_equal("[2]"));
    
    output << queue.head();
    BOOST_CHECK(output.is_equal("2"));
}

BOOST_AUTO_TEST_SUITE_END()
  
BOOST_AUTO_TEST_SUITE(test_enQueue)

BOOST_AUTO_TEST_CASE(empty)
{
    Queue<int> queue;

    queue.enQueue(1);

    boost::test_tools::output_test_stream out;
    out << queue;
    BOOST_CHECK(out.is_equal("[1]"));
    BOOST_CHECK_EQUAL(queue.size(), 1);
}

BOOST_AUTO_TEST_CASE(normal)
{
    int arr[5] = {1, 1, 1, 1, 1};
    Queue<int> queue(arr, 5);

    queue.enQueue(2);

    boost::test_tools::output_test_stream out;
    out << queue;
    BOOST_CHECK(out.is_equal("[1 | 1 | 1 | 1 | 1 | 2]"));
    BOOST_CHECK_EQUAL(queue.size(), 6);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_deQueue)

BOOST_AUTO_TEST_CASE(one)
{
    Queue<int> queue(1);
    int head = queue.deQueue();
    BOOST_CHECK_EQUAL(queue.size(), 0);
    BOOST_CHECK_EQUAL(head, 1);
}

BOOST_AUTO_TEST_CASE(normal)
{
    int arr[5] = {1, 2, 3, 4, 5};
    Queue<int> queue(arr, 5);
    int head = queue.deQueue();
    boost::test_tools::output_test_stream out;
    out << queue;
    BOOST_CHECK(out.is_equal("[2 | 3 | 4 | 5]"));
    BOOST_CHECK_EQUAL(head, 1);
    head = queue.deQueue();
    out << queue;
    BOOST_CHECK(out.is_equal("[3 | 4 | 5]"));
    BOOST_CHECK_EQUAL(head, 2);
}

BOOST_AUTO_TEST_SUITE_END()



