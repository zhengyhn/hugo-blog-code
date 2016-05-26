#include <iostream>

template <typename T>
void
swap(T& a, T& b)
{
    if (a != b) {
        T tmp = a;
        a = b;
        b = tmp;
    }
}

template <typename T>
void
reverse(T list[], int begin, int end)
{
    if (list == NULL || begin >= end - 1) {
        return;
    }
    while (begin < end) {
        swap(list[begin], list[end - 1]);
        ++begin;
        --end;
    }
}

template <typename T>
void
exchange(T list[], int begin, int mid, int end)
{
    reverse(list, begin, mid);
    reverse(list, mid, end);
    reverse(list, begin, end);
}

template <typename T>
void
merge(T list[], int begin, int mid, int end, bool is_ascending)
{
    int first = begin;
    int second = mid;

    while (first < second && second < end) {
        while (first < second &&
               ((is_ascending && list[first] < list[second]) ||
                (!is_ascending && list[first] > list[second]))) {
            ++first;
        }
        while (second < end &&
               ((is_ascending && list[second] < list[first]) ||
                (!is_ascending && list[second] > list[first]))) {
            ++second;
        }
        exchange(list, first, mid, second);
        first += second - mid;
    }
}
                      
template <typename T>
void
merge_sort_exchange(T list[], int begin, int end, bool is_ascending=true)
{
    if (list == NULL || begin >= end - 1) {
        return;
    }
    int mid = (begin + end) / 2;

    merge_sort(list, begin, mid, is_ascending);
    merge_sort(list, mid, end, is_ascending);
    merge(list, begin, mid, end, is_ascending);
}
