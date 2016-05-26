#ifndef _CILIST_H_
#define _CILIST_H_

#include <iostream>
#include <cassert>

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

template <typename T>
class CiLinkedList {
public:
    explicit CiLinkedList()
        :head_(NULL), size_(0)
    { }

    explicit CiLinkedList(const T& value)
        :head_(new Node<T>(value)), size_(1)
    { this->head_->next(this->head_); }

    explicit CiLinkedList(const T values[], const size_t& size)
	:head_(NULL), size_(size)
    {
	if (size == 1) {
	    this->head_ = new Node<T>(values[0]);
	    this->head_->next(this->head_);
	} else if (size > 1) {
	    this->head_ = new Node<T>(values[0]);
	    Node<T> *p = this->head_;
	    for (int i = 1; i < size; ++i) {
		Node<T> *node = new Node<T>(values[i]);
		p->next(node);
		p = p->next();
	    }
	    p->next(this->head_);
	}
    }

    explicit CiLinkedList(const CiLinkedList& list)
	:head_(NULL), size_(list.size_)
    {
	Node<T> *pright = list.head_;
	if (pright != NULL) {
	    this->head_ = new Node<T>(pright->value());
	    Node<T> *pleft = this->head_;
	    while (pright->next() != list.head_) {
		pright = pright->next();
		Node<T> *node = new Node<T>(pright->value());
		pleft->next(node);
		pleft = pleft->next();
	    }
	    pleft->next(this->head_);
	}
    }
	
    const CiLinkedList&
    operator=(const CiLinkedList& list)
    {
	if (this->head_ == list.head_) {
	    return *this;
	}
	this->clean();
	this->size_ = list.size_;
	if (list.head_ != NULL) {
	    Node<T> *p = list.head_;
	    this->head_ = new Node<T>(p->value());
	    Node<T> *thisp = this->head_;
	    p = p->next();
	    while (p != list.head_) {
		Node<T> *node = new Node<T>(p->value());
		thisp->next(node);
		thisp = thisp->next();
		p = p->next();
	    }
	    thisp->next(this->head_);
	}
	return *this;
    }
	
    ~CiLinkedList()
    { this->clean(); }

    const size_t&
    size() const
    { return this->size_; }

    const T&
    operator[](const size_t& index)
    {
	assert(index >= 0 && index <= this->size_);
	size_t i = 0;
	Node<T> *p = this->head_;
	while (i < index) {
	    p = p->next();
	    ++i;
	}
	return p->value();
    }
	
    friend std::ostream&
    operator<<(std::ostream& os, const CiLinkedList<T>& list)
    {
	Node<T> *p = list.head_;
	std::string seperator = "";
	os << '[';
	if (p != NULL) {
	    while (p->next() != list.head_) {
		os << seperator << p->value();
		p = p->next();
		seperator = ", ";
	    }
	    os << seperator << p->value();
	}
	os << ']';
	return os;
    }

    void
    rm_dup()
    {
	if (this->size_ <= 1) {
	    return;
	}
	Node<T> *p = this->head_;
	while (p->next() != this->head_) {
	    Node<T> *pprev = p;
	    Node<T> *pnext = p->next();
	    while (pnext != this->head_) {
		if (p->value() == pnext->value()) {
		    pprev->next(pnext->next());
		    delete pnext;
		    --this->size_;
		    pnext = pprev->next();
		} else {
		    pprev = pnext;
		    pnext = pprev->next();
		}
	    }
	    p = p->next();
	}
    }
private:
    Node<T> *head_;
    size_t size_;

    void
    clean()
    {
	Node<T> *p = this->head_;
	while (p != NULL) {
	    if (this->size_ == 1) {
		delete p;
		--this->size_;
		break;
	    } else if (p == this->head_) {
		Node<T> *temp = p;
		p = p->next();
		temp->next(NULL);
	    } else {
		Node<T> *to_delete = p;
		p = p->next();
		delete to_delete;
		--this->size_;
	    }
	}
	this->head_ = NULL;
    }
};

#endif /* _CILIST_H_ */


