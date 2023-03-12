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
#include "utility.hpp"
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
template<typename T>
struct Node
{
  typedef Node* pointer;
  typedef Node const * const_pointer;

  pointer parent;
  pointer left;
  pointer right;
  T key;
  RBTreeColor color;
  pointer const nill;

  Node(T const &_key, pointer const &leaf, RBTreeColor color = red)
    : parent(0), left(0), right(0), key(_key), color(color), nill(leaf) {}

  static pointer getAncestor(pointer current)
  {
    pointer ancestor;

    if (current->left == 0 && current->right == 0)
      return current->parent;

    if (current->left != current->nill)
      return maximum(current->left);

    ancestor = current->parent;
    while (ancestor != current->nill && current == ancestor->left)
    {
      current = ancestor;
      ancestor = ancestor->parent;
    }
    return ancestor;
  }

  static const_pointer getAncestor(const_pointer current)
  {
    return getAncestor(const_cast<pointer>(current));
  }

  static pointer getSuccessor(pointer ancestor)
  {
    pointer successor;

    if (ancestor->right != ancestor->nill)
      return minimum(ancestor->right);

    successor = ancestor->parent;
    while (successor != ancestor->nill && successor->right == ancestor)
    {
      ancestor = successor;
      successor = successor->parent;
    }
    return successor;
  }

  static const_pointer getSuccessor(const_pointer ancestor)
  {
    return getSuccessor(const_cast<pointer>(ancestor));
  }

  static pointer maximum(pointer current)
  {
    while (current->right != current->nill)
      current = current->right;
    return current;
  }

  static pointer minimum(pointer current)
  {
    while (current->left != current->nill)
      current = current->left;
    return current;
  }
};

template<typename T>
struct RBTreeIterator
{

  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef std::ptrdiff_t difference_type;

  typedef typename Node<T>::pointer nodePointer;

  nodePointer current;


  RBTreeIterator() : current(0) {}
  RBTreeIterator(nodePointer const &current) : current(current) {}

  reference operator*() { return current->key; }
  pointer operator->() { return &current->key; }

  RBTreeIterator& operator++()
  {
    current = Node<T>::getSuccessor(current);
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
    current = Node<T>::getAncestor(current);
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

  bool operator!=(RBTreeIterator const &other) const
  {
    return !(*this == other);
  }
}; // end of RBTreeIterator


template<typename T>
struct RBTreeConstIterator
{

  typedef T value_type;
  typedef T const & reference;
  typedef T const * pointer;
  typedef std::ptrdiff_t difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;

  typedef typename Node<T>::pointer nodePointer;

  nodePointer current;

  RBTreeConstIterator() : current(0) {}
  RBTreeConstIterator(nodePointer const &__new) : current(__new) {}

  reference operator*() const { return current->key; }
  pointer operator->() const { return &current->key; }

  RBTreeConstIterator &operator++()
  {
    current = Node<T>::getSuccessor(current);
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
    current = Node<T>::getAncestor(current);
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

  bool operator!=(RBTreeConstIterator const &other) const
  {
    return !(*this == other);
  }
};

template<typename T>
bool operator==(RBTreeIterator<T> const &lhs, RBTreeConstIterator<T> const &rhs)
{
  return lhs.current == rhs.current;
}

template<typename T>
bool operator!=(RBTreeIterator<T> const &lhs, RBTreeConstIterator<T> const &rhs)
{
  return !(lhs == rhs);
}

template<
  class Key,
  class T,
  class KeyOfValue,
  class Compare = std::less<Key>,
  class Alloc = std::allocator<T>
>
class RBTree
{

public:
  typedef T                                       value_type;
  typedef value_type &                            reference;
  typedef value_type const &                      const_reference;
  typedef Key                                     key_type;
  typedef Compare                                 key_compare;
  typedef size_t                                  size_type;
  typedef ptrdiff_t                               difference_type;

  typedef Alloc                                   allocator_type;
  typedef typename Alloc::pointer                 pointer;
  typedef typename Alloc::const_pointer           const_pointer;
  typedef typename Alloc::template rebind<Node<T> >::other nodeAllocator;

  typedef RBTreeIterator<value_type>              iterator;
  typedef RBTreeConstIterator<value_type const>   const_iterator;
  typedef ft::reverse_iterator<iterator>          reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

private:
  typedef Node<value_type>                        node_type;
  typedef typename node_type::pointer             nodePointer;

  node_type      _base;
  nodePointer    _root;
  size_type      _count;

public:

  RBTree() : _base(value_type(), &_base, black), _root(_base.nill), _count(0) {}

  ~RBTree()
  {
    while (_root != _base.nill)
      erase(getKey(_root->key));
  }

  //capacity
  bool empty() const { return _count == 0; }
  size_type size() const { return _count; }

  //modifiers
  ft::pair<iterator, bool> insert_unique(value_type const &value)
  {
    iterator searchedKey = find(getKey(value));

    if (searchedKey != end())
      return ft::make_pair(searchedKey, false);

    return ft::make_pair(_insert(value), true);
  }

  void erase(key_type const &key)
  {
    iterator toDelete;

    toDelete = find(key);
    if (toDelete != end())
    {
      _delete(toDelete.current);
      deleteNode(toDelete.current);
      --_count;
      if (_root != _base.nill)
        _base.parent = node_type::maximum(_root);
    }
  }

  iterator find(key_type const &key)
  {
    nodePointer current = _root;
    key_compare fnCompare;

    while (current != _base.nill && getKey(current->key) != key)
      if (fnCompare(key, getKey(current->key)))
        current = current->left;
      else
        current = current->right;
    return current;
  }


  iterator begin() { return node_type::minimum(_root); }
  iterator end() { return &_base; }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }

  const_iterator begin() const { return node_type::minimum(_root); }
  const_iterator end() const { return &_base; }

  const_reverse_iterator rbegin() const
  {
    return const_reverse_iterator(end());
  }

  const_reverse_iterator rend() const
  {
    return const_reverse_iterator(begin());
  }

  nodePointer const &getRoot() const { return _root; }
  void printTree() const { printHelper(_root, "", true); }

private:

  iterator _insert(value_type const &value)
  {
    nodePointer current;
    nodePointer previous;
    nodePointer newNode;

    current = _root;
    previous = _base.nill;
    newNode = getAllocatorNodeType().allocate(1);
    getAllocatorNodeType().construct(newNode, node_type(value, _base.nill));

    while (current != _base.nill)
    {
      previous = current;
      if (compareKeys(value, current->key))
        current = current->left;
      else
        current = current->right;
    }

    newNode->parent = previous;

    if (previous == _base.nill)
      _root = newNode;
    else if (compareKeys(newNode->key, previous->key))
      previous->left = newNode;
    else
      previous->right = newNode;
    newNode->left = _base.nill;
    newNode->right = _base.nill;

    insertFixup(newNode);
    _base.parent = node_type::maximum(_root);
    ++_count;

    return iterator(newNode);
  }

  allocator_type getAllocatorValueType() const { return allocator_type(); }
  nodeAllocator getAllocatorNodeType() const { return nodeAllocator(); }

  void deleteNode(nodePointer toDelete)
  {
    getAllocatorValueType().destroy(&toDelete->key);
    getAllocatorNodeType().deallocate(toDelete, 1);
  }

  key_type const &getKey(value_type const &__key) const
  {
    return KeyOfValue()(__key);
  }

  bool compareKeys(value_type const &lhs, value_type const &rhs) const
  {
    return key_compare()(getKey(lhs), getKey(rhs));
  }

  // private attributes
  void _delete(nodePointer z)
  {
    nodePointer sucessorSubTree;
    nodePointer sucessor = z;
    RBTreeColor original_color = sucessor->color;

    if (z->left == _base.nill)
    {
      sucessorSubTree = z->right;
      transplant(z, z->right);
    }
    else if (z->right == _base.nill)
    {
      sucessorSubTree = z->left;
      transplant(z, z->left);
    }
    else
    {
      sucessor = node_type::minimum(z->right);
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

  void deleteFixup(nodePointer x)
  {
    nodePointer xSibling;

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

  void transplant(nodePointer from, nodePointer to)
  {
    if (from->parent == _base.nill)
      _root = to;
    else if (from == from->parent->left)
      from->parent->left = to;
    else
      from->parent->right = to;
    to->parent = from->parent;
  }

  void insertFixup(nodePointer z)
  {
    nodePointer uncle;

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


  void leftRotate(nodePointer a)
  {
    nodePointer const rightSubTree = a->right;

    a->right = rightSubTree->left;

    if (rightSubTree->left != _base.nill)
      rightSubTree->left->parent = a;

    rightSubTree->parent = a->parent;

    if (a->parent == _base.nill)
      _root = rightSubTree;

    else if (a == a->parent->left)
      a->parent->left = rightSubTree;

    else
      a->parent->right = rightSubTree;

    rightSubTree->left = a;
    a->parent = rightSubTree;
  }

  void rightRotate(nodePointer a)
  {
    nodePointer const leftSubTree = a->left;

    a->left = leftSubTree->right;

    if (leftSubTree->right != _base.nill)
      leftSubTree->right->parent = a;

    leftSubTree->parent = a->parent;

    if (a->parent == _base.nill)
      _root = leftSubTree;

    else if (a->parent->left == a)
      a->parent->left = leftSubTree;

    else
      a->parent->right = leftSubTree;

    a->parent = leftSubTree;
    leftSubTree->right = a;
  }

  void printHelper(nodePointer root, std::string indent, bool last) const
  {
    if (root != _base.nill)
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
      std::cout << root->key.second << "(" << color << ")" << std::endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }
  }

}; // end of RBTree

} // namespace end

#endif // !RB_TREE_HPP
