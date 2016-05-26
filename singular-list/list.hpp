#ifndef _CAREERUP_LIST_H_
#define _CAREERUP_LIST_H_

#include <iostream>

#undef NDEBUG
#include <cassert>

/* This class template is the Node of a singular linked list
 * value_: the value store in the node.
 * next_: the pointer that points to the next node. */
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

/* The singular linked list class template,
 * head_: a pointer pointing to the head of the list
 * size_: the length of the list */
template <typename T>
class LinkedList {
public:
    explicit LinkedList()
        :size_(0), head_(NULL)
    { }
    explicit LinkedList(const LinkedList& list)
        :size_(list.size_), head_(NULL)
    {
        Node<T> *p = list.head_;
        if (p != NULL) {
            Node<T> *node = new Node<T>(p->value());
            this->head_ = node;
            p = p->next();
        }
        Node<T> *thisp = this->head_;
        while (p != NULL) {
            Node<T> *node = new Node<T>(p->value());
            thisp->next(node);
            thisp = thisp->next();
        }
    }

    // Create from a head node of value VALUE.
    explicit LinkedList(const T& value)
        :size_(1), head_(new Node<T>(value))
    { }

    // Create from an array VALUES of size SIZE.
    explicit LinkedList(const T values[], size_t size)
        :size_(size), head_(NULL)
    {
        if (size > 0) {
            this->head_ = new Node<T>(values[0]);
            Node<T> *p = this->head_;
            for (size_t i = 1; i < size; ++i) {
                Node<T> *node = new Node<T>(values[i]);
                p->next(node);
                p = p->next();
            }
        }
    }
    
    const LinkedList&
    operator=(const LinkedList& list)
    {
        // The same list
        if (this->head_ == list.head_) {
            return *this;
        }
        this->clean();
        this->size_ = list.size_;
        Node<T> *pright = list.head_;
        if (pright != NULL) {
            this->head_ = new Node<T>(pright->value());
            pright = pright->next();
            Node<T> *pleft = this->head_;
            while (pright != NULL) {
                pleft->next(new Node<T>(pright->value()));
                pleft = pleft->next();
                pright = pright->next();
            }
        }
        return *this;
    }
        
    ~LinkedList()
    { this->clean(); }

    // Output a list in the form [a, b, c, ...].
    friend std::ostream&
    operator<<(std::ostream& os, const LinkedList<T>& list)
    {
        Node<T> *p = list.head_;
        std::string separator = "";
        os << '[';
        while (p != NULL) {
            os << separator << p->value();
            separator = ", ";
            p = p->next();
        }
        os << ']';
        return os;
    }
        
    // Add an element of value VALUE to the back of the list.
    void
    append(const T& value)
    {
        Node<T> *node = new Node<T>(value);
        Node<T> *p = this->head_;
        if (p == NULL) {
            this->head_ = node;
        } else {
            while (p->next() != NULL) {
                p = p->next();
            }
            p->next(node);
        }

        ++this->size_;
    }
        
    // Return the value of the element in the position of INDEX.
    const T&
    operator[](size_t index) const
    { return this->get(index); }

    // Insert an element of value VALUE into the position INDEX.
    void
    insert(size_t index, const T& value)
    {
        assert(index >= 0 && index <= this->size_);
        Node<T> *p = this->head_;
        if (index == 0) {
            Node<T> *node = new Node<T>(value, p);
            this->head_ = node;
        } else if (index == this->size_) {
            while (p->next() != NULL) {
                p = p->next();
            }
            Node<T> *node = new Node<T>(value);
            p->next(node);
        } else {
            int i = 1;
            while (i < index) {
                p = p->next();
                ++i;
            }
            Node<T> *node = new Node<T>(value, p->next());
            p->next(node);
        }
        ++this->size_;
    }
        
    // Remove the element in the position INDEX.
    void
    remove(size_t index)
    {
        if (index < 0 || index >= this->size_) {
            return;
        }
        Node<T> *p = this->head_;
        if (p == NULL) {
            return;
        }
        if (index == 0) {
            this->head_ = p->next();
            delete p;
        } else {
            int i = 1;
            while (i < index) {
                p = p->next();
                ++i;
            }
            Node<T> *to_delete = p->next();
            p->next(to_delete->next());
            delete to_delete;
        }
        --this->size_;
    }

    size_t
    size() const
    { return this->size_; }

    void
    reverse()
    {
        if (this->size_ <= 1) {
            return;
        }
        Node<T> *p = this->head_;
        Node<T> *prev = p;
        Node<T> *next = p->next();
        prev->next(NULL);
        while (next->next() != NULL) {
            p = next;
            next = p->next();
            p->next(prev);
            prev = p;
        }
        p = next;
        p->next(prev);
        this->head_ = p;
    }

    // Sort the list in the ascending order according to the type
    // of the value of the elements.
    void
    sort()
    { this->head_ = merge_sort(this->head_, this->size_); }

    // Remove duplicate elements.
    void
    rm_dup()
    {
        if (this->size_ <= 1) {
            return;
        }
        for (Node<T> *pleft = this->head_;
             pleft != NULL && pleft->next() != NULL;
             pleft = pleft->next()) {
            for (Node<T> *pright = pleft->next(), *pprev = pleft;
                 pright != NULL;) {
                if (pleft->value() == pright->value()) {
                    pprev->next(pright->next());
                    delete pright;
                    --this->size_;
                    pright = pprev->next();
                } else {
                    pprev = pright;
                    pright = pright->next();
                }
            }
        }
    }
        
    // Return the nth to last element. i.e, 2th to last element of
    // list 1->2->3->4 is 2.
    const T&
    nth_to_last(size_t n) const
    { return this->get(this->size_ - n - 1); }
private:
    size_t size_;
    Node<T> *head_;

    Node<T> *
    merge_sort(Node<T> *head, size_t len)
    {
        if (len < 1) {
            return head;
        } else if (len < 2) {
            head->next(NULL);
            return head;
        } else {
            int i = 0;
            Node<T> *p = head;
            while (i < len / 2) {
                p = p->next();
                ++i;
            }
            head = merge_sort(head, len / 2);
            p = merge_sort(p, len - len / 2);
            return merge(head, p);
        }
    }
        
    Node<T> *
    merge(Node<T> *lhs, Node<T> *rhs)
    {
        Node<T> *pright = rhs;
        Node<T> *pleft = lhs;
        Node<T> *pleft_prev = lhs;
        if (rhs->value() < lhs->value()) {
            pright = rhs->next();
            rhs->next(lhs);
            lhs = rhs;
            pleft_prev = lhs;
            pleft = lhs->next();
        }
        while (pleft != NULL && pright != NULL) {
            if (pright->value() < pleft->value()) {
                pleft_prev->next(pright);
                pright = pright->next();
                pleft_prev = pleft_prev->next();
                pleft_prev->next(pleft);
                pleft = pleft_prev->next();
            } else {
                pleft_prev = pleft;
                pleft = pleft->next();
            }
        }
        while (pright != NULL) {
            pleft_prev->next(pright);
            pleft_prev = pleft_prev->next();
            pright = pright->next();
        }
        return lhs;
    }
        
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

    const T&
    get(size_t index) const
    {
        assert(index >= 0 && index < this->size_);
        int i = 0;
        Node<T> *p = this->head_;
        while (i < index) {
            p = p->next();
            ++i;
        }
        return p->value();
    }
};

#endif /* _CAREERUP-LIST_H_ */
