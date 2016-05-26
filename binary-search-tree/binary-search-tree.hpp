#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

#include <iostream>
#include <sstream>
#include <functional>
#include <vector>

// Tree node.
template <typename T>
class Node {
public:
  Node()
    :value_(), lch_(NULL), rch_(NULL), parent_(NULL)
  { }

  Node(const T& value, Node<T> *lch=NULL,
       Node<T> *rch=NULL, Node<T> *parent=NULL)
    :value_(value), lch_(lch), rch_(rch), parent_(parent)
  { }

  ~Node() { }

  // Return the data stored in the node.
  const T&
  value() const
  { return this->value_; }

  // Change the data to V.
  void
  value(const T& v)
  { this->value_ = v; }

  Node<T> *
  left_child() const
  { return this->lch_; }

  void
  left_child(Node<T> *lch)
  { this->lch_ = lch; }

  Node<T> *
  right_child() const
  { return this->rch_; }

  void
  right_child(Node<T> *rch)
  { this->rch_ = rch; }

  Node<T> *
  parent() const
  { return this->parent_; }
    
  void
  parent(Node<T> *parent)
  { this->parent_ = parent; }

  friend std::ostream
  operator<<(std::ostream& os, const Node<T>& node)
  { return os << node.value(); }
private:
  // Cannot be copied.
  explicit Node(const Node<T>& node);
    
  const Node<T>&
  operator=(const Node<T>& node);

  // Data stored.
  T value_;

  // Left child.
  Node<T> *lch_;

  // Right child.
  Node<T> *rch_;

  // Parent.
  Node<T> *parent_;
};

// BinarySearchTree, the "Node" is invisible from outside.
template <typename T>
class BinarySearchTree {
public:
  BinarySearchTree()
    :root_(NULL)
  { }

  // [root_val] is the data to be stored in the root node.
  explicit BinarySearchTree(const T& root_val)
    :root_(new Node<T>(root_val))
  { }

  BinarySearchTree(const T values[], const size_t& size)
    :root_(NULL)
  {
    if (values == NULL || size <= 0) {
      return;
    }
    
    this->root_ = new Node<T>(values[0]);
    for (int i = 1; i < size; ++i) {
      this->insert(values[i]);
    }
  }
    
  BinarySearchTree(const BinarySearchTree<T>& tree)
    :root_(NULL)
  { this->root_ = new_nodes(this->root_, tree.root_); }

  // This assignment function's implementation is not so effecient,
  // just create a new tree from the [tree] and swap the data with the
  // current tree, and then automatically delete the new tree.
  const BinarySearchTree&
  operator=(const BinarySearchTree& tree)
  {
    if (this != &tree) {
      BinarySearchTree tmp(tree);
      Node<T> *p = tmp.proot();
      tmp.proot(this->root_);
      this->root_ = p;
    }
    return *this;
  }

  // Delete the nodes in postorder.
  ~BinarySearchTree()
  {
    auto del_fun = std::bind(&BinarySearchTree<T>::del_node,
                             this, std::placeholders::_1);
    postorder(this->root_, del_fun);
  }

  // This function just return the root pointer.
  Node<T> *
  proot() const
  { return this->root_; }

  void
  proot(Node<T> *root)
  { this->root_ = root; }

  // But this function return the data stored in the root node.
  const T&
  root() const
  { return this->root_->value(); }

  bool
  is_empty() const
  { return this->root_ == NULL; }

  // Insert a node, duplicating is allowed.
  void
  insert(const T& value)
  {
    Node<T> *p = this->root_;

    if (p == NULL) {
      this->root_ = new Node<T>(value);
      return;
    }
    while (p != NULL) {
      if (value < p->value()) {
        if (p->left_child() == NULL) {
          Node<T> *node = new Node<T>(value);
          node->parent(p);
          p->left_child(node);
          break;
        } else {
          p = p->left_child();
        }
      } else {
        if (p->right_child() == NULL) {
          Node<T> *node = new Node<T>(value);
          node->parent(p);
          p->right_child(node);
          break;
        } else {
          p = p->right_child();
        }
      }
    }
  }

  // Return the inorder travel's string, just for testing.
  std::string
  inorder_string() const
  {
    std::string result = this->inorder_str(this->root_);
    if (result != "") {
      result.erase(0, 1);
      result[0] = '[';        
    } else {
      result.append(1, '[');
    }
    result.append(1, ']');
        
    return result;
  }

  // Return the data after search the tree in terms of the [key]. There
  // may be more than one item, since we allow duplicating.
  T
  retrieve(const T& key)
  { return this->search(this->root_, key); }

  // Remove a node in terms of the [key].
  void
  remove(const T& key)
  { this->delete_nodes(this->root_, key); }

  friend bool
  operator==(const BinarySearchTree<T>& left,
             const BinarySearchTree<T>& right)
  { return is_equal(left.root_, right.root_); }
private:
  Node<T> *root_;
    
  std::string
  inorder_str(Node<T> *root) const
  {
    std::string result = "";
    std::string seperator = ", ";
    if (root != NULL) {
      if (root->left_child() != NULL) {
        result += this->inorder_str(root->left_child());
      }
      std::stringstream ss;
      ss << seperator << root->value();
      result += ss.str();
      if (root->right_child() != NULL) {
        result += this->inorder_str(root->right_child());
      }
    }
    return result;
  }

  void
  postorder(Node<T> *root, const std::function<void(Node<T> *)>& func)
  {
    if (root != NULL) {
      this->postorder(root->left_child(), func);
      this->postorder(root->right_child(), func);
      func(root);
    }
  }

  void
  del_node(Node<T> *node)
  {
    if (node != NULL) {
      delete node;
    }
  }

  void
  inorder(Node<T> *root, const std::function<void(void)>& func)
  {
    if (root != NULL) {
      this->inorder(root->left_child(), func);
      func(root);
      this->inorder(root->right_child(), func);
    }
  }

  void
  preorder(Node<T> *root, const std::function<void(void)>& func)
  {
    if (root != NULL) {
      func(root);
      this->preorder(root->left_child(), func);
      this->preorder(root->right_child(), func);
    }
  }
    
  Node<T> *
  new_nodes(Node<T> *dest, const Node<T> *src)
  {
    if (src != NULL) {
      if (dest == NULL) {
        dest = new Node<T>(src->value());
      }
      if (src->left_child() != NULL) {
        Node<T> *node = new_nodes(dest->left_child(),
                                  src->left_child());
        node->parent(dest);
        dest->left_child(node);
      }
      if (src->right_child() != NULL) {
        Node<T> *node = new_nodes(dest->right_child(),
                                  src->right_child());
        node->parent(dest);
        dest->right_child(node);
      }
    }
    return dest;
  }

  T
  search(Node<T> *root, const T& key)
  {
    while (root != NULL) {
      if (key == root->value()) {
        return root->value();
      } else if (key < root->value()) {
        root = root->left_child();
      } else {
        root = root->right_child();
      }
    }
  }

  // [single] is whether delete a single element or multiple element of the
  // same value.
  void
  delete_nodes(Node<T> *root, const T& key)
  {
    if (root != NULL) {
      if (key < root->value()) {
        this->delete_nodes(root->left_child(), key);
      } else if (key > root->value()) {
        this->delete_nodes(root->right_child(), key);
      } else {
        if (root->left_child() != NULL &&
            root->right_child() != NULL) { // If have two children
          Node<T> *predecessor =
            this->mini_node(root->right_child());
          root->value(predecessor->value());
          this->delete_nodes(predecessor, predecessor->value());
        } else if (root->left_child() != NULL) { // One child(left)
          if (root == this->root_) {
            this->root_ = root->left_child();
          } else if (root->parent()->left_child() == root) {
            root->parent()->left_child(root->left_child());
            root->left_child()->parent(root->parent());
          } else {
            root->parent()->right_child(root->left_child());
            root->left_child()->parent(root->parent());
          }
          Node<T> *to_delete = root;
          root = root->left_child();
          delete to_delete;
        } else if (root->right_child() != NULL) {  // Right
          if (root == this->root_) {
            this->root_ = root;
          } else if (root->parent()->left_child() == root) {
            root->parent()->left_child(root->right_child());
            root->right_child()->parent(root->parent());    
          } else {
            root->parent()->right_child(root->right_child());
            root->right_child()->parent(root->parent());   
          }
          Node<T> *to_delete = root;
          root = root->right_child();
          delete to_delete;
        } else {                  // The leaf
          Node<T> *to_delete = root;
          if (this->root_ == root) {
            this->root_ = NULL;
          } else if (root->parent()->left_child() == root) {
            root->parent()->left_child(NULL);
          } else {
            root->parent()->right_child(NULL);
          }
          delete to_delete;
        }
      }
    }
  }

  // Find a node of the smallest value in a subtree.
  Node<T> *
  mini_node(Node<T> *root) const
  {
    Node<T> *min = root;
    while (min != NULL && min->left_child() != NULL) {
      min = min->left_child();
    }
    return min;
  }
};

#endif /* _BINARY_SEARCH_TREE_H_ */

template <typename T>
bool
is_equal(Node<T> *left, Node<T> *right)
{
  if ((left == NULL && right != NULL) ||
      (left != NULL && right == NULL)) {
    return false;
  } else if (left == NULL && right == NULL) {
    return true;
  } else if (left->value() != right->value()) {
    return false;
  } else {
    return (is_equal(left->left_child(), right->left_child()) &&
            is_equal(left->right_child(), right->right_child())) ||
      (is_equal(left->left_child(), right->right_child()) &&
       is_equal(left->right_child(), right->left_child()));
  }
}
