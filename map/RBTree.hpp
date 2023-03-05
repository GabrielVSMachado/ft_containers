/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:56:27 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/02/18 13:56:36 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <cstddef>
#include <iterator>
#include <memory>
#include <iostream>
#include "ReverseIterator.hpp"
#include "iterator.hpp"

namespace internals
{

enum RBTreeColor
{
  red = true,
  black = false
};


/**
 * Structure used as Node for the Red-Black Tree.
**/
struct Node
{
  typedef Node* pointer;
  typedef Node const * const_pointer;

  pointer parent;
  pointer left;
  pointer right;
  int key;
  RBTreeColor color;
  pointer const _nill;

  Node(int const &_key, pointer const &leaf, RBTreeColor color = red)
    : parent(0), left(0), right(0), key(_key), color(color), _nill(leaf) {}

  static pointer getAncestor(pointer current)
  {
    pointer ancestor;

    if (current->left == 0 && current->right == 0)
      return current->parent;

    if (current->left != current->_nill)
      return maximum(current->left);

    ancestor = current->parent;
    while (ancestor != current->_nill && current == ancestor->left)
    {
      current = ancestor;
      ancestor = ancestor->parent;
    }
    return ancestor;
  }

  static const_pointer getAncestor(const_pointer current)
  {
    return Node::getAncestor(const_cast<pointer>(current));
  }

  static pointer getSuccessor(pointer ancestor)
  {
    pointer successor;

    if (ancestor->right != ancestor->_nill)
      return minimum(ancestor->right);

    successor = ancestor->parent;
    while (successor != ancestor->_nill && successor->right == ancestor)
    {
      ancestor = successor;
      successor = successor->parent;
    }
    return successor;
  }

  static const_pointer getSuccessor(const_pointer ancestor)
  {
    return Node::getSuccessor(const_cast<pointer>(ancestor));
  }

  static pointer maximum(pointer current)
  {
    while (current->right != current->_nill)
      current = current->right;
    return current;
  }

  static pointer minimum(pointer current)
  {
    while (current->left != current->_nill)
      current = current->left;
    return current;
  }
};

struct RBTreeIterator
{

  typedef std::bidirectional_iterator_tag iterator_category;
  typedef Node value_type;
  typedef Node::pointer pointer;
  typedef Node & reference;
  typedef std::ptrdiff_t difference_type;

  pointer current;

  RBTreeIterator() : current(0) {}
  RBTreeIterator(pointer const &current) : current(current) {}

  reference operator*() { return *current; }
  pointer operator->() { return current; }

  RBTreeIterator& operator++()
  {
    current = Node::getSuccessor(current);
    return *this;
  }

  RBTreeIterator operator++(int)
  {
    RBTreeIterator prev = *this;
    operator++();
    return prev;
  }

  RBTreeIterator& operator--()
  {
    current = Node::getAncestor(current);
    return *this;
  }

  RBTreeIterator operator--(int)
  {
    RBTreeIterator prev = *this;
    operator--();
    return prev;
  }

  bool operator==(RBTreeIterator const &other) const
  {
    return current == other.current;
  }
  bool operator!=(RBTreeIterator const &other) const { return !(*this == other); }
}; // end of RBTreeIterator


struct RBTreeConstIterator
{
  typedef Node value_type;
  typedef Node const & reference;
  typedef Node const * pointer;
  typedef std::ptrdiff_t difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;

  pointer current;

  RBTreeConstIterator() : current(0) {}
  RBTreeConstIterator(pointer const &__new) : current(__new) {}

  reference operator*() { return *current; }
  pointer operator->() { return current; }

  RBTreeConstIterator &operator++()
  {
    current = Node::getSuccessor(current);
    return  *this;
  }

  RBTreeConstIterator operator++(int)
  {
    RBTreeConstIterator oldValue = *this;
    operator++();
    return oldValue;
  }

  RBTreeConstIterator &operator--()
  {
    current = Node::getAncestor(current);
    return *this;
  }

  RBTreeConstIterator operator--(int)
  {
    RBTreeConstIterator oldValue = *this;
    operator--();
    return oldValue;
  }

  bool operator==(RBTreeConstIterator const &other) const
  {
    return other.current == current;
  }

  bool operator!=(RBTreeConstIterator const &other) const { return !(*this == other); }
};

bool operator==(RBTreeIterator const &lhs, RBTreeConstIterator const &rhs)
{
  return lhs.current == rhs.current;
}

bool operator!=(RBTreeIterator const &lhs, RBTreeConstIterator const &rhs)
{
  return !(lhs == rhs);
}

class RBTree
{

public:
  typedef Node::pointer pointer;
  typedef int value_type;
  typedef RBTreeIterator iterator;
  typedef RBTreeConstIterator const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  RBTree() : base(0, &base, black), _root(base._nill) {}
  ~RBTree()
  {
    while (_root != base._nill)
      deleteKey(_root->key);
  }

  /**
   * Insert new Node with given value.
   *
   * @value: value which has the same type of the Node's key variable;
   *
  **/
  void insert(value_type const &value)
  {
    pointer current = _root;
    pointer previous = base._nill;
    pointer newNode = new Node(value, &base);

    while (current != base._nill)
    {
      previous = current;
      current = !(value < current->key) ? current->right : current->left;
    }
    newNode->parent = previous;

    if (previous == base._nill)
      _root = newNode;
    else if (newNode->key < previous->key)
      previous->left = newNode;
    else
      previous->right = newNode;
    newNode->left = base._nill;
    newNode->right = base._nill;

    insertFixup(newNode);
    base.parent = Node::maximum(_root);
  }

  void deleteKey(value_type const &key)
  {
    pointer toDelete;

    toDelete = search(key);
    _delete(toDelete);
    if (_root != base._nill)
      base.parent = Node::maximum(_root);
    delete toDelete;
  }

  iterator begin() { return Node::minimum(_root); }
  iterator end() { return &base; }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }

  const_iterator begin() const { return Node::minimum(_root); }
  const_iterator end() const { return &base; }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
  const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

  void printTree() const { printHelper(_root, "", true); }

private:

  // private attributes
  Node base;
  pointer _root;

  pointer search(value_type const &key)
  {
    pointer current = _root;

    while (current != base._nill && current->key != key)
      current = !(key < current->key) ? current->right : current->left;
    return current;
  }

  void _delete(pointer z)
  {
    pointer sucessorSubTree;
    pointer sucessor = z;
    unsigned int original_color = sucessor->color;

    if (z->left == base._nill)
    {
      sucessorSubTree = z->right;
      transplant(z, z->right);
    }
    else if (z->right == base._nill)
    {
      sucessorSubTree = z->left;
      transplant(z, z->left);
    }
    else
    {
      sucessor = Node::minimum(z->right);
      original_color = sucessor->color;
      sucessorSubTree = sucessor->right;
      if (sucessor != z->right)
      {
        transplant(sucessor, sucessor->right);
        sucessor->right = z->right;
        sucessor->right->parent = sucessor;
      }
      else
        sucessorSubTree->parent = sucessor;

      transplant(z, sucessor);
      sucessor->left = z->left;
      sucessor->left->parent = sucessor;
      sucessor->color = z->color;
    }

    if (original_color == black)
      deleteFixup(sucessorSubTree);
  }

  void deleteFixup(pointer x)
  {
    pointer xSibling;

    while (x != _root && x->color == black)
    {
      if (x == x->parent->right)
      {
        xSibling = x->parent->left;

        if (xSibling->color == red)
        {
          xSibling->color = black;
          x->parent->color = red;
          rightRotate(x->parent);
          xSibling = x->parent->left;
        }

        if (xSibling->left->color == black && xSibling->right->color == black)
        {
          xSibling->color = red;
          x = x->parent;
        }
        else
        {
          if (xSibling->left->color == black)
          {
            xSibling->color = red;
            xSibling->right->color = black;
            leftRotate(xSibling);
            xSibling = x->parent->left;
          }
          xSibling->color = x->parent->color;
          x->parent->color = black;
          xSibling->left->color = black;
          rightRotate(x->parent);
          x = _root;
        }
      }
      else
      {
        xSibling = x->parent->right;

        if (xSibling->color == red)
        {
          xSibling->color = black;
          x->parent->color = red;
          leftRotate(x->parent);
          xSibling = x->parent->right;
        }

        if (xSibling->left->color == black && xSibling->right->color == black)
        {
          xSibling->color = red;
          x = x->parent;
        }
        else
        {
          if (xSibling->right->color == black)
          {
            xSibling->left->color = black;
            xSibling->color = red;
            rightRotate(xSibling);
            xSibling = x->parent->right;
          }
          xSibling->color = x->parent->color;
          x->parent->color = black;
          xSibling->right->color = black;
          leftRotate(x->parent);
          x = _root;
        }
      }
    }
    x->color = black;
  }

  void transplant(pointer from, pointer to)
  {
    if (from->parent == base._nill)
      _root = to;
    else if (from == from->parent->left)
      from->parent->left = to;
    else
      from->parent->right = to;
    to->parent = from->parent;
  }

  void insertFixup(pointer z)
  {
    pointer uncle;

    while (z->parent->color == red)
    {
      if (z->parent == z->parent->parent->left)
      {
        uncle = z->parent->parent->right;
        if (uncle->color == red)
        {
          uncle->color = black;
          z->parent->color = black;
          z->parent->parent->color = red;
          z = z->parent->parent;
        }
        else
        {
          if (z == z->parent->right)
          {
            z = z->parent;
            leftRotate(z);
          }
          z->parent->color = black;
          z->parent->parent->color = red;
          rightRotate(z->parent->parent);
        }
      }
      else
      {
        uncle = z->parent->parent->left;
        if (uncle->color == red)
        {
          uncle->color = black;
          z->parent->color = black;
          z->parent->parent->color = red;
          z = z->parent->parent;
        }
        else
        {
          if (z == z->parent->left)
          {
            z = z->parent;
            rightRotate(z);
          }
          z->parent->color = black;
          z->parent->parent->color = red;
          leftRotate(z->parent->parent);
        }
      }
    }
    _root->color = black;
  }


  void leftRotate(pointer a)
  {
    pointer const rightSubTree = a->right;

    a->right = rightSubTree->left;

    if (rightSubTree->left != base._nill)
      rightSubTree->left->parent = a;

    rightSubTree->parent = a->parent;

    if (a->parent == base._nill)
      _root = rightSubTree;

    else if (a == a->parent->left)
      a->parent->left = rightSubTree;

    else
      a->parent->right = rightSubTree;

    rightSubTree->left = a;
    a->parent = rightSubTree;
  }

  void rightRotate(pointer a)
  {
    pointer const leftSubTree = a->left;

    a->left = leftSubTree->right;

    if (leftSubTree->right != base._nill)
      leftSubTree->right->parent = a;

    leftSubTree->parent = a->parent;

    if (a->parent == base._nill)
      _root = leftSubTree;

    else if (a->parent->left == a)
      a->parent->left = leftSubTree;

    else
      a->parent->right = leftSubTree;

    a->parent = leftSubTree;
    leftSubTree->right = a;
  }

  void printHelper(pointer root, std::string indent, bool last) const
  {
    if (root != base._nill)
    {
      std::cout << indent;
      if (last) {
        std::cout << "R----";
        indent += "    ";
      } else {
        std::cout << "L----";
        indent += "|    ";
      }

      char const r[] = "\x1b[31mRed\033[0m";
      char const b[] = "\x1b[34mBlack\033[0m";
      std::string color = root->color ? r : b;
      std::cout << root->key << "(" << color << ")" << std::endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }
  }

}; // end of RBTree

} // namespace end

#endif // !RB_TREE_HPP
