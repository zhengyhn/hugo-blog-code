#include "st-queue.h"

template <typename T>
std::ostream&
operator<<(std::ostream& os, const StQueue<T>& queue)
{
    Node<T> *pout = queue.out_stack_->ptop();
    Node<T> *pin = queue.in_stack_->ptop();
    std::string seperator = "";

    os << '[';
    while (pout != NULL) {
        os << seperator << pout->value();
        seperator = " | ";
        pout = pout->next();
    }
    if (pin != NULL) {
        Stack<T> temp;
        while (pin != NULL) {
            temp.push(pin->value());
            pin = pin->next();
        }
        while (temp.size() > 0) {
            os << seperator << temp.pop();
            seperator = " | ";
        }
    }
    os << ']';
    return os;
}

