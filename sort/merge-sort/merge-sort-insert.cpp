#include <iostream>

template <typename T>
void
merge(T list[], int begin, int mid, int end, bool is_ascending)
{
    for (int i = mid; i < end; ++i) {
        T tmp = list[i];
        int j;
        for (j = i - 1; j >= begin; --j) {
            if ((is_ascending && list[j] < tmp) ||
                (!is_ascending && list[j] > tmp)) {
                list[j + 1] = list[j];
            } else {
                break;
            }
        }
        list[j + 1] = tmp;
    }
}
                      
template <typename T>
void
merge_sort_insert(T list[], int begin, int end, bool is_ascending=true)
{
    if (list == NULL || begin >= end - 1) {
        return;
    }
    int mid = (begin + end) / 2;

    merge_sort(list, begin, mid, is_ascending);
    merge_sort(list, mid, end, is_ascending);
    merge(list, begin, mid, end, is_ascending);
}
