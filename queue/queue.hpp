#ifndef _QUEUE_H_
#define _QUEUE_H_

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
class Queue {
public:
    explicit Queue()
        :head_(NULL), tail_(NULL), size_(0)
    { }

    explicit Queue(const T& value)
        :head_(new Node<T>(value)), tail_(head_), size_(1)
    { }

    explicit Queue(const T values[], const size_t& size)
        :head_(NULL), tail_(NULL), size_(size)
    {
        if (size > 0) {
            this->head_ = new Node<T>(values[0]);
            this->tail_ = this->head_;
            for (int i = 1; i < size; ++i) {
                Node<T> *node = new Node<T>(values[i]);
                this->tail_->next(node);
                this->tail_ = this->tail_->next();
            }
        }
    }

    explicit Queue(const Queue<T>& queue)
        :head_(NULL), tail_(NULL), size_(queue.size_)
    {
        if (this->size_ > 0) {
            Node<T> *p = queue.head_;
            this->head_ = new Node<T>(p->value());
            this->tail_ = this->head_;
            p = p->next();
            while (p != NULL) {
                Node<T> *node = new Node<T>(p->value());
                this->tail_->next(node);
                this->tail_ = this->tail_->next();
                p = p->next();
            }
        }
    }

    const Queue<T>&
    operator=(const Queue<T>& queue)
    {
        if (this->head_ == queue.head_) {
            return *this;
        }
        if (queue.size_ > 0) {
            Node<T> *pleft = this->head_;
            Node<T> *pright = queue.head_;
            while (pright != NULL) {
                if (pleft == NULL) {
                    pleft = new Node<T>(pright->value());
                } else {
                    pleft->value(pright->value());
                }
                pright = pright->next();
                this->tail_ = pleft;
                pleft = pleft->next();
            }
            while (pleft != NULL) {
                Node<T> *to_delete = pleft;
                pleft = pleft->next();
                delete to_delete;
            }
            this->tail_->next(NULL);
        }
        this->size_ = queue.size_;
        return *this;
    }

    ~Queue()
    { this->clean(); }

    friend std::ostream&
    operator<<(std::ostream& os, const Queue<T>& queue)
    {
        std::string seperator = "";
        Node<T> *p = queue.head_;
        os << '[';
        while (p != NULL) {
            os << seperator << p->value();
            p = p->next();
            seperator = " | ";
        }
        os << ']';
        return os;
    }
        
    const T&
    head() const
    {
        if (this->size_ == 0) {
            std::cerr << "The queue is empty!\n";
            exit(1);
        }
        return this->head_->value();
    }   

    size_t
    size() const
    { return this->size_; }
    
    void
    enQueue(const T& value)
    {
        Node<T> *node = new Node<T>(value);
        if (this->size_ == 0) {
            this->head_ = node;
            this->tail_ = node;
        } else {
            this->tail_->next(node);
            this->tail_ = this->tail_->next();
        }
        ++this->size_;
    }

    const T
    deQueue()
    {
        if (this->size_ == 0) {
            std::cerr << "Cannot pop an empty queue\n";
            exit(1);
        } else {
            T value = this->head_->value();
            Node<T> *to_delete = this->head_;
            if (this->size_ == 1) {
                this->head_ = this->tail_ = NULL;
            } else {
                this->head_ = this->head_->next();
            }
            delete to_delete;
            --this->size_;
            return value;
        }
    }
private:
    Node<T> *head_;
    Node<T> *tail_;
    size_t size_;

    void
    clean()
    {
        Node<T> *p = this->head_;
        while (p != NULL) {
            Node<T> *to_delete = p;
            p = p->next();
            delete to_delete;
            --this->size_;
        }
        this->head_ = this->tail_ = NULL;
    }
};

#endif /* _QUEUE_H_ */
