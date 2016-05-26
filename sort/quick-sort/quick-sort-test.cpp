#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <cstdlib>
#include <algorithm>
#include <boost/test/unit_test.hpp>
#include "quick-sort.cpp"

int empty_list[0];

const int NORMAL_SIZE = 5;
int normal_list[NORMAL_SIZE] = {5, 1, 4, 2, 8};
int normal_list_sorted[NORMAL_SIZE] = {1, 2, 4, 5, 8};
int normal_list_sorted_descend[NORMAL_SIZE] = {8, 5, 4, 2, 1};

const int RANDOM_SIZE = 200000;

BOOST_AUTO_TEST_SUITE(quick_recursive)

BOOST_AUTO_TEST_CASE(empty)
{
    qsort_r(empty_list, 0, 0);
}

BOOST_AUTO_TEST_CASE(two_element)
{
  const int NUM = 2;
  int arr[NUM] = {2, 1};

  qsort_r(arr, 0, NUM);
  BOOST_CHECK_EQUAL(arr[0], 1);
  BOOST_CHECK_EQUAL(arr[1], 2);
}

BOOST_AUTO_TEST_CASE(normal)
{
    qsort_r(normal_list, 0, NORMAL_SIZE);
    for (int i = 0; i < NORMAL_SIZE; ++i) {
        BOOST_CHECK_EQUAL(normal_list[i], normal_list_sorted[i]);
    }
}

BOOST_AUTO_TEST_CASE(normal_descending)
{
    qsort_r(normal_list, 0, NORMAL_SIZE, false);
    for (int i = 0; i < NORMAL_SIZE; ++i) {
        BOOST_CHECK_EQUAL(normal_list[i], normal_list_sorted_descend[i]);
    }
}

BOOST_AUTO_TEST_CASE(random)
{
    int *random_list = new int[RANDOM_SIZE];
    int *random_list_sorted = new int[RANDOM_SIZE];
    srand(1);
    for (int i = 0; i < RANDOM_SIZE; ++i) {
        random_list[i] = random_list_sorted[i] = rand();
    }
    qsort_r(random_list, 0, RANDOM_SIZE);
    std::sort(random_list_sorted, random_list_sorted + RANDOM_SIZE);
    for (int i = 0; i < RANDOM_SIZE; ++i) {
        BOOST_CHECK_EQUAL(random_list[i], random_list_sorted[i]);
    }
    delete[] random_list;
    delete[] random_list_sorted;
}

BOOST_AUTO_TEST_SUITE_END()

