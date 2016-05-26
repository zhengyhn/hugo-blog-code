#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <stack>
#include <cstdlib>

bool
is_digit(char c)
{ return c >= '0' && c <= '9'; }

bool
is_operator(char c)
{ return c == '+' || c == '-' || c == '*' || c == '/'; }

// Convert infix expression to postfix expression
// The EXP cannot be empty string.
// Negative number in the middle of the expression must be in a bracket.
const std::string
infix2postfix(const std::string& exp)
{
    std::stack<char> operators;
    std::string postfix;
    
    for (unsigned i = 0; i < exp.size(); ++i) {
        if (exp[i] == ' ') {
            continue;
        }
        if (exp[i] == '(') {
            if (exp[i + 1] == '-') {
                for (unsigned j = i + 2; j < exp.size(); ++j) {
                    if (is_digit(exp[j])) {
                        continue;
                    } else if (exp[j] == ')') {
                        postfix.append(exp, i, j - i + 1);
                        i = j;
                        break;
                    } else {
                        break;
                    }
                }
            }
            operators.push(exp[i]);
        } else if (exp[i] == ')') {
            while (!operators.empty()) {
                char op = operators.top();
                operators.pop();                                
                if (op == '(') {
                    break;
                } else {
                    postfix.push_back(op);
                }
            }
        } else if (exp[i] == '+' || exp[i] == '-') {
            if (exp[i] == '-' && (i == 0)) {
                postfix.push_back('(');
                postfix.push_back(exp[i]);
                unsigned j;
                for (j = i + 1; j < exp.size(); ++j) {
                    if (is_digit(exp[j])) {
                        postfix.push_back(exp[j]);
                    } else {
                        break;
                    }
                }
                i += j - i - 1;
                postfix.push_back(')');
                continue;
            }
            while (!operators.empty()) {
                char op = operators.top();
                if (op == '(') {
                    break;
                } else {
                    postfix.push_back(op);
                }
                operators.pop();                
            }
            operators.push(exp[i]);
        } else if (exp[i] == '*' || exp[i] == '/') {
            operators.push(exp[i]);
        } else if (is_digit(exp[i])) {
            postfix.push_back('(');
            postfix.push_back(exp[i]);
            unsigned j;
            for (j = i + 1; j < exp.size(); ++j) {
                if (is_digit(exp[j])) {
                    postfix.push_back(exp[j]);
                } else {
                    break;
                }
            }
            i += j - i - 1;
            postfix.push_back(')');
        } else {
            std::cerr << "Invalid character.\n";
            exit(1);
        }
    }
    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();
        postfix.push_back(op);
    }
    return postfix;
}

int
atoi(const std::string& exp, int idx, int num)
{
    int sign = 1;
    if (exp[idx] == '-') {
        sign = -sign;
        ++idx;
        --num;
    }
    int result = 0;
    while (num > 0) {
        result = result * 10 + exp[idx] - '0';
        ++idx;
        --num;
    }
    return result * sign;
}

double
calculate(double left, double right, char op)
{
    double result = 0.0;
    
    switch (op) {
    case '+':
        result = left + right;
        break;
    case '-':
        result = left - right;
        break;
    case '*':
        result = left * right;
        break;
    case '/':
        result = left / right;
        break;
    default:
        break;
    }
    return result;
}

// Evaluate an infix expression, support only '+', '-', '*', '/' operators.
// The operand must be integer(positive, negative or 0). Using brackets is ok.
double
evaluate(const std::string& infix_exp)
{
    if (infix_exp == "") {
        return 0.0;
    }
    const std::string exp = infix2postfix(infix_exp);
    std::stack<double> numbers;
    for (unsigned i = 0; i < exp.size(); ++i) {
        if (exp[i] == '(') {
            int count = 0;
            while (exp[i + count + 1] != ')') {
                ++count;
            }
            int n = atoi(exp, i + 1, count);
            numbers.push(n);
            i += count + 1;
        } else if (!is_digit(exp[i])) {
            double right = numbers.top();
            numbers.pop();
            double left = numbers.top();
            numbers.pop();
            double result = calculate(left, right, exp[i]);
            numbers.push(result);
        } else {
            std::cerr << "Invalid postfix expression.\n";
            exit(1);
        }
    }
    return numbers.top();
}

BOOST_AUTO_TEST_SUITE(infix_to_postfix)

BOOST_AUTO_TEST_CASE(simple)
{
    std::string result = infix2postfix("1 + 1");
    BOOST_CHECK_EQUAL(result, "(1)(1)+");
    result = infix2postfix("2 - 10");
    BOOST_CHECK_EQUAL(result, "(2)(10)-");
    result = infix2postfix("-2 - 10");
    BOOST_CHECK_EQUAL(result, "(-2)(10)-");
    result = infix2postfix("(-2) * (-10)");
    BOOST_CHECK_EQUAL(result, "(-2)(-10)*");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_evaluate)

BOOST_AUTO_TEST_CASE(empty)
{
    double result = evaluate("");
    BOOST_CHECK_EQUAL(result, 0.0);
}

BOOST_AUTO_TEST_CASE(very_simple)
{
    double result = evaluate("1 + 1");
    BOOST_CHECK_EQUAL(result, 2.0);
    result = evaluate("1 - 1");
    BOOST_CHECK_EQUAL(result, 0.0);
    result = evaluate("2 * 3");
    BOOST_CHECK_EQUAL(result, 6.0);
    result = evaluate("2 / 3");
    BOOST_CHECK_EQUAL(result, 2.0 / 3);
}

BOOST_AUTO_TEST_CASE(negative)
{
    double result = evaluate("2 * (-3) + 2 - (-2) - (-2) / 3");
    BOOST_CHECK_EQUAL(result, 2 * (-3) + 2 - (-2) - (-2) / 3.0);
}

BOOST_AUTO_TEST_CASE(complex)
{
    const char *exp = "9 + (3 - 1) * 3 + 10 / 2";
    double result = evaluate(exp);
    BOOST_CHECK_EQUAL(result, 20.0);

    const char *exp2 = "9 + 3 - 1 * 3 + 10 / 2";
    result = evaluate(exp2);
    BOOST_CHECK_EQUAL(result, 14.0);
}

BOOST_AUTO_TEST_CASE(more_complex)
{
    const char *exp = "(((123 + 456) * (321 - 654) + (-444)) / (-333))";
    double result = evaluate(exp);
    BOOST_CHECK_EQUAL(result, (((123 + 456) * (321 - 654) + (-444)) / (-333.0)));
    
    const char *exp2 = "((((1 + 2) * 3 + 4) * 5) + 6) * 7 + 8";
    result = evaluate(exp2);
    BOOST_CHECK_EQUAL(result, ((((1 + 2) * 3 + 4) * 5) + 6) * 7 + 8.0);
}

BOOST_AUTO_TEST_SUITE_END()


