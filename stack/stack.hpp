#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>
#include <cstdlib>

template <typename T>
class Node {
public:
    explicit Node()
        :value_(), next_(NULL)
    { }
    explicit Node(const Node& n)
        :value_(n.value_), next_(n.next_)
    { }
    explicit Node(const T& value, Node<T> *next=NULL)
    {
        this->value_ = value;
        this->next_ = next;
    }
    const Node&
    operator=(const Node& n)
    {
        this->value_ = n.value_;
        this->next_ = n.next_;
        return *this;
    }
    ~Node() { }

    friend std::ostream&
    operator << (std::ostream& os, const Node& node)
    { return os << node.value_; }

    const T&
    value() const
    { return this->value_; }

    // Set the node's value to VALUE.
    void
    value(const T& value)
    { this->value_ = value; }

    Node<T> *
    next() const
    { return this->next_; }

    // Set the 'next_' pointer to the pointer NEXT.
    void
    next(Node<T> *next)
    { this->next_ = next; }
private:
    Node<T> *next_;
    T value_;
};

template <typename T>
class Stack {
public:
    explicit Stack()
        :top_(NULL), size_(0)
    { }
    
    explicit Stack(const T& value)
        :top_(new Node<T>(value)), size_(1)
    { }

    explicit Stack(const T values[], const size_t& size)
        :top_(NULL), size_(size)
    {
        if (size > 0) {
            this->top_ = new Node<T>(values[0]);
            for (int i = 1; i < size; ++i) {
                Node<T> *node = new Node<T>(values[i], this->top_);
                this->top_ = node;
            }
        }
    }

    explicit Stack(const Stack<T>& stack)
        :top_(NULL), size_(stack.size_)
    {
        if (stack.size_ > 0) {
            Node<T> *p = stack.top_;
            this->top_ = new Node<T>(p->value());
            p = p->next();
            while (p != NULL) {
                Node<T> *node = new Node<T>(p->value(), this->top_);
                this->top_ = node;
                p = p->next();
            }
        }
    }

    const Stack<T>&
    operator=(const Stack<T>& stack)
    {
        Node<T> *pleft = this->top_;    
        Node<T> *pright = stack.top_;

        if (pleft == pright) {
            return *this;
        }
        if (pright != NULL) {
            if (pleft == NULL) {
                pleft = new Node<T>(pright->value());
                this->top_ = pleft;
            } else {
                pleft->value(pright->value());
            }
            pright = pright->next();
        }
        while (pright != NULL) {
            if (pleft->next() == NULL) {
                Node<T> *node = new Node<T>(pright->value());
                pleft->next(node);
            } else {
                Node<T> *p = pleft->next();
                p->value(pright->value());
            }
            pleft = pleft->next();
            pright = pright->next();
        }
        Node<T> *pprev = pleft;
        pleft = pleft->next();
        pprev->next(NULL);
        while (pleft != NULL) {
            Node<T> *to_delete = pleft;
            pleft = pleft->next();
            delete to_delete;
        }
        this->size_ = stack.size_;
        return *this;
    }

    ~Stack()
    {
        Node<T> *p = this->top_;
        while (p != NULL) {
            Node<T> *to_delete = p;
            p = p->next();
            delete to_delete;
        }
        this->top_ = NULL;
    }
    
    friend std::ostream&
    operator<<(std::ostream& os, const Stack<T>& stack)
    {
        Node<T> *p = stack.top_;
        std::string seperator = "";
        os << "[";
        while (p != NULL) {
            os << seperator << p->value();
            seperator = " | ";
            p = p->next();
        }
        os << "]";
        return os;
    }
    
    const T&
    top() const
    { return this->top_->value(); }

    void
    push(const T& value)
    {
        Node<T> *node = new Node<T>(value, this->top_);
        this->top_ = node;
        ++this->size_;
    }

    const T
    pop()
    {
        Node<T> *to_delete = this->top_;
        this->top_ = this->top_->next();
        T top_value = to_delete->value();
        delete to_delete;
        --this->size_;
        return top_value;
    }

    const size_t&
    size() const
    { return this->size_; }

    Node<T> *
    ptop() const
    { return this->top_; }
private:
    Node<T> *top_;
    size_t size_;
};

#endif /* _STACK_H_ */
