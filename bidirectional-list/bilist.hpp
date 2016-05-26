#ifndef _BILIST_H_
#define _BILIST_H_

#include <iostream>
#include <cassert>

template <typename T>
class Node {
public:
    explicit Node()
        :value_(), prev_(NULL), next_(NULL)
    { }

    explicit Node(const T& value, Node *prev=NULL, Node *next=NULL)
        :value_(value), prev_(next), next_(next)
    { }

    explicit Node(const Node& node)
        :value_(node.value_), prev_(node.prev_), next_(node.next_)
    { }

    const Node&
    operator=(const Node& node)
    {
        this->value_ = node.value_;
        this->prev_ = node.prev_;
        this->next_ = node.next_;
    }

    ~Node() { }

    Node<T> *
    next() const
    { return this->next_; }

    const T&
    value() const
    { return this->value_; }

    void
    next(Node<T> *next)
    { this->next_ = next; }

    void
    prev(Node<T> *prev)
    { this->prev_ = prev; }

    friend std::ostream&
    operator<<(std::ostream& os, const Node<T>& node)
    { return os << node.value_; }
private:
    T value_;
    Node *prev_;
    Node *next_;
};

template <typename T>
class BiLinkedList {
public:
    explicit BiLinkedList()
        :head_(NULL), size_(0)
    { }

    explicit BiLinkedList(const T& value)
        :head_(new Node<T>(value)), size_(1)
    { }

    explicit BiLinkedList(const T values[], size_t size)
        :head_(NULL), size_(size)
    {
        if (this->size_ > 0) {
            this->head_ = new Node<T>(values[0]);
            Node<T> *p = this->head_;
            for (size_t i = 1; i < size; ++i) {
                Node<T> *node = new Node<T>(values[i], p, NULL);
                p->next(node);
                p = p->next();
            }
        }
    }

    explicit BiLinkedList(const BiLinkedList& blist)
        :head_(NULL), size_(blist.size_)
    {
        Node<T> *p = blist.head_;
        if (p != NULL) {
            Node<T> *node = new Node<T>(p->value());
            this->head_ = node;
            p = p->next();
        }
        Node<T> *thisp = this->head_;
        while (p != NULL) {
            Node<T> *node = new Node<T>(p->value(), thisp);
            thisp->next(node);
            thisp = thisp->next();
            p = p->next();
        }
    }
        
    const BiLinkedList&
    operator=(const BiLinkedList& blist)
    {
        if (this->head_ == blist.head_) {
            return *this;
        }
        this->clean();
        this->size_ = blist.size_;
        Node<T> *p = blist.head_;
        if (p != NULL) {
            this->head_ = new Node<T>(p->value());
            Node<T> *thisp = this->head_;
            p = p->next();
            while (p != NULL) {
                Node<T> *node = new Node<T>(p->value(), thisp);
                thisp->next(node);
                thisp = thisp->next();
                p = p->next();
            }
        }
        return *this;   
    }
        
    ~BiLinkedList()
    { this->clean(); }

    size_t
    size() const
    { return this->size_; }

    friend std::ostream&
    operator<<(std::ostream& os, const BiLinkedList<T>& list)
    {
        std::string seperator = "";
        Node<T> *p = list.head_;
        os << '[';
        while (p != NULL) {
            os << seperator << p->value();
            seperator = ", ";
            p = p->next();
        }
        os << ']';
        return os;
    }
        
    const T&
    operator[](const size_t& index)
    {
        assert(index >= 0 && index < this->size_);
        Node<T> *p = this->head_;
        size_t i = 0;
        while (i < index) {
            ++i;
            p = p->next();
        }
        return p->value();
    }
        
    void
    append(const T& value)
    {
        Node<T> *p = this->head_;
        if (p == NULL) {
            this->head_ = new Node<T>(value);
        } else {
            while (p->next() != NULL) {
                p = p->next();
            }
            Node<T> *node = new Node<T>(value, p);
            p->next(node);
        }
        ++this->size_;
    }
        
    void
    insert(size_t index, const T& value)
    {
        assert(index >= 0 && index <= this->size_);
        if (index == 0) {
            Node<T> *node = new Node<T>(value, NULL, this->head_);
            if (this->head_ != NULL) {
                this->head_->prev(node);
            }
            this->head_ = node;
        } else if (index == this->size_) {
            Node<T> *p = this->head_;
            while (p->next() != NULL) {
                p = p->next();
            }
            Node<T> *node = new Node<T>(value, p);
            p->next(node);
        } else {
            Node<T> *p = this->head_;
            size_t i = 1;
            while (i < index) {
                p = p->next();
                ++i;
            }
            Node<T> *node = new Node<T>(value, p, p->next());
            p->next()->prev(node);
            p->next(node);
        }
        ++this->size_;
    }
        
    void
    remove(size_t index)
    {
        if (this->head_ == NULL) {
            return;
        }
        if (index == 0) {
            Node<T> *to_delete = this->head_;
            Node<T> *p = this->head_->next();
            p->prev(NULL);
            delete to_delete;
            this->head_ = p;
        } else {
            size_t i = 0;
            Node<T> *p = this->head_;
            while (i < index - 1) {
                p = p->next();
                ++i;
            }
            Node<T> *to_delete = p->next();
            p->next(to_delete->next());
            if (p->next() != NULL) {
                p->next()->prev(p);
            }
            delete to_delete;
        }
        --this->size_;
    }
private:
    Node<T> *head_;
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
        this->head_ = NULL;
    }
};

#endif /* _BILIST_H_ */    
