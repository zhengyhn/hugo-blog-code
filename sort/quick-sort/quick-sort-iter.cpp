#include <iostream>

template <typename T>
inline void         // Inline, may be faster.
swap(T& a, T& b)
{
    if (a != b) {  // If the same, there's no need to swap.
        T tmp = a;
        a = b;
        b = tmp;
    }
}

template <typename T>
void
qsort_i(T arr[], int begin, int end, bool is_ascending=true)
{
    if (arr == NULL || begin >= end - 1) {
        return;
    }
    int *stack = new int[end - begin];
    int top = -1;

    stack[++top] = end;
    stack[++top] = begin;

    while (top > 0) {
        begin = stack[top];
        --top;
        end = stack[top];
        --top;

        swap(arr[(begin + end - 1) / 2], arr[end - 1]);
        int pivot = end - 1;
        int last_left = begin - 1;
        for (int i = begin; i < end - 1; ++i) {
            if ((is_ascending && arr[i] < arr[pivot]) ||
                (!is_ascending && arr[i] > arr[pivot])) {
                swap(arr[i], arr[++last_left]);
            }
        }
        swap(arr[pivot], arr[++last_left]);

        if (last_left > begin + 1) {
            stack[++top] = last_left;
            stack[++top] = begin;
        }
        if (last_left < end - 2) {
            stack[++top] = end;
            stack[++top] = last_left + 1;
        }
    }
    delete[] stack;
}
