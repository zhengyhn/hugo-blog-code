#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "stack.hpp"

BOOST_AUTO_TEST_SUITE(test_create)

BOOST_AUTO_TEST_CASE(create_empty)
{
    Stack<int> stack;
    BOOST_CHECK_EQUAL(stack.size(), 0);

    int arr[5];
    Stack<int> stack2(arr, 0);
    BOOST_CHECK_EQUAL(stack2.size(), 0);
}

BOOST_AUTO_TEST_CASE(create_with_one_element)
{
    Stack<int> stack_int(1);
    BOOST_CHECK_EQUAL(stack_int.size(), 1);
    BOOST_CHECK_EQUAL(stack_int.top(), 1);

    Stack<char> stack_char('a');
    BOOST_CHECK_EQUAL(stack_char.size(), 1);
    BOOST_CHECK_EQUAL(stack_char.top(), 'a');

    Stack<double> stack_double(1.23);
    BOOST_CHECK_EQUAL(stack_double.size(), 1);
    BOOST_CHECK_EQUAL(stack_double.top(), 1.23);

    Stack<std::string> stack_str("abc");
    BOOST_CHECK_EQUAL(stack_str.size(), 1);
    BOOST_CHECK_EQUAL(stack_str.top(), "abc");
}

BOOST_AUTO_TEST_CASE(create_with_an_array)
{
    int arr[5] = {1, 2, 3, 4, 5};
    Stack<int> stack(arr, 5);
    boost::test_tools::output_test_stream output;
    output << stack;
    BOOST_CHECK(output.is_equal("[5 | 4 | 3 | 2 | 1]"));
}

BOOST_AUTO_TEST_CASE(create_copy_empty)
{
    Stack<int> *stack1 = new Stack<int>();
    Stack<int> stack2(*stack1);
    delete stack1;
    BOOST_CHECK_EQUAL(stack2.size(), 0);
}

BOOST_AUTO_TEST_CASE(create_copy_one)
{
    Stack<int> *stack1 = new Stack<int>(3);
    Stack<int> stack2(*stack1);
    delete stack1;
    BOOST_CHECK_EQUAL(stack2.size(), 1);
    BOOST_CHECK_EQUAL(stack2.top(), 3);
}

BOOST_AUTO_TEST_CASE(create_and_assign)
{
    int arr[3] = {1, 2, 3};
    Stack<int> stack1(arr, 3);

    int a[2] = {4, 5};
    Stack<int> stack2(a, 2);

    stack1 = stack2;
    boost::test_tools::output_test_stream output;
    output << stack1;
    BOOST_CHECK(output.is_equal("[5 | 4]"));

    stack1 = stack1;
    BOOST_CHECK_EQUAL(stack1.size(), 2);
    output << stack1;
    BOOST_CHECK(output.is_equal("[5 | 4]"));
}

BOOST_AUTO_TEST_CASE(assign_empty)
{
    Stack<int> stack1(2);
    Stack<int> stack2;
    stack1 = stack2;
    BOOST_CHECK_EQUAL(stack1.size(), 0);
    stack1 = stack1;
    BOOST_CHECK_EQUAL(stack1.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_output)

BOOST_AUTO_TEST_CASE(ouput_empty)
{
    Stack<int> stack;
    boost::test_tools::output_test_stream output;
    output << stack;
    BOOST_CHECK(output.is_equal("[]"));
}

BOOST_AUTO_TEST_CASE(output_one)
{
    Stack<int> stack(2);
    boost::test_tools::output_test_stream output;
    output << stack;
    BOOST_CHECK(output.is_equal("[2]"));
    
    output << stack.top();
    BOOST_CHECK(output.is_equal("2"));
}

BOOST_AUTO_TEST_SUITE_END()
  
BOOST_AUTO_TEST_SUITE(test_push)

BOOST_AUTO_TEST_CASE(empty)
{
    Stack<int> stack;

    stack.push(1);

    boost::test_tools::output_test_stream out;
    out << stack;
    BOOST_CHECK(out.is_equal("[1]"));
    BOOST_CHECK_EQUAL(stack.size(), 1);
}

BOOST_AUTO_TEST_CASE(normal)
{
    int arr[5] = {1, 1, 1, 1, 1};
    Stack<int> stack(arr, 5);

    stack.push(2);

    boost::test_tools::output_test_stream out;
    out << stack;

    BOOST_CHECK(out.is_equal("[2 | 1 | 1 | 1 | 1 | 1]"));
    BOOST_CHECK_EQUAL(stack.size(), 6);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_pop)

BOOST_AUTO_TEST_CASE(one)
{
    Stack<int> stack(1);
    int head = stack.pop();
    BOOST_CHECK_EQUAL(stack.size(), 0);
    BOOST_CHECK_EQUAL(head, 1);
}

BOOST_AUTO_TEST_CASE(normal)
{
    int arr[5] = {1, 2, 3, 4, 5};
    Stack<int> stack(arr, 5);
    int head = stack.pop();
    boost::test_tools::output_test_stream out;
    out << stack;
    BOOST_CHECK(out.is_equal("[4 | 3 | 2 | 1]"));
    BOOST_CHECK_EQUAL(head, 5);
    head = stack.pop();
    out << stack;
    BOOST_CHECK(out.is_equal("[3 | 2 | 1]"));
    BOOST_CHECK_EQUAL(head, 4);
}

BOOST_AUTO_TEST_SUITE_END()



