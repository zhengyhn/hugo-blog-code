#include <iostream>

template <typename T>
void
select_sort(T list[], const int& size, bool is_ascending=true)
{
    if (list == NULL || size <= 1) {
        return;
    }
    for (int i = 0; i < size - 1; ++i) {
        int k = i;
        for (int j = k + 1; j < size; ++j) {
            if ((is_ascending && list[j] < list[k]) ||
                (!is_ascending && list[j] > list[k])) {
                    k = j;
            }
        }
        if (k != i) {
            T tmp = list[i];
            list[i] = list[k];
            list[k] = tmp;
        }
    }
}
