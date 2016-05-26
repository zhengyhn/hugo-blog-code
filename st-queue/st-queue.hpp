#include <iostream>
#include "stack.hpp"

template <typename T>
class StQueue {
public:
    explicit StQueue()
        :in_stack_(new Stack<T>()), out_stack_(new Stack<T>()), size_(0)
    { }

    explicit StQueue(const T& value)
        :in_stack_(new Stack<T>(value)), out_stack_(new Stack<T>()), size_(1)
    { }

    explicit StQueue(const T values[], const size_t& size)
        :in_stack_(new Stack<T>(values, size)), out_stack_(new Stack<T>()),
         size_(size)
    { }

    explicit StQueue(const StQueue<T>& queue)
        :in_stack_(new Stack<T>(*queue.in_stack_)),
         out_stack_(new Stack<T>(*queue.out_stack_)),
         size_(queue.size_)
    { }

    const StQueue<T>&
    operator=(const StQueue<T>& queue)
    {
        if (this->in_stack_ == queue.in_stack_
            && this->out_stack_ == queue.out_stack_) {
            return *this;
        }
        *(this->in_stack_) = *(queue.in_stack_);
        *(this->out_stack_) = *(queue.out_stack_);
        this->size_ = queue.size_;
        return *this;
    }

    ~StQueue()
    {
        if (this->in_stack_ != NULL) {
            delete this->in_stack_;
        }
        if (this->out_stack_ != NULL) {
            delete this->out_stack_;
        }
    }
    
    friend std::ostream&
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

    void
    enQueue(const T& value)
    {
        this->in_stack_->push(value);
        ++this->size_;
    }

    const T
    deQueue()
    {
        if (this->size_ <= 0) {
            std::cerr << "The queue is empty!\n";
            exit(1);
        }
        if (this->out_stack_->size() <= 0) {
            while (this->in_stack_->size() > 0) {
                this->out_stack_->push(this->in_stack_->pop());
            }
        }
        --this->size_;  
        return this->out_stack_->pop();
    }

    const size_t&
    size() const
    { return this->size_; }

    const T&
    head() const
    {
        if (this->size_ <= 0) {
            std::cerr << "The queue is empty!\n";
            exit(1);
        }
        if (this->out_stack_->size() <= 0) {
            while (this->in_stack_->size() > 0) {
                this->out_stack_->push(this->in_stack_->pop());
            }
        }
        return this->out_stack_->top();
    }
private:
    Stack<T> *in_stack_;
    Stack<T> *out_stack_;
    size_t size_;
};
