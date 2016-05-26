#include <iostream>

template <typename T>
void
insert_sort(T list[], const int& size, bool is_ascending=true)
{
    if (list == NULL || size <= 1) {
        return;
    }
    for (int i = 1; i < size; ++i) {
        T tmp = list[i]; 
        int j;
        for (j = i - 1; j >= 0; --j) {
            if ((is_ascending && tmp < list[j]) ||
                (!is_ascending && tmp > list[j])) {
                    list[j + 1] = list[j];
            } else {
                break;
            }
        }
        list[j + 1] = tmp;
    }
}


        
