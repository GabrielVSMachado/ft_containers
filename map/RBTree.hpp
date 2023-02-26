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

#include <memory>
#include <iostream>

namespace internals
{

class RBTree
{
  static unsigned int const red;
  static unsigned int const black;

public:

  RBTree() : _nill(new Node(0, black)), _root(_nill) {}
  ~RBTree()
  {
    while (_root != _nill)
      deleteKey(_root->key);
    delete _nill;
  }

  /**
   * Insert new Node with given value.
   *
   * @value: value which has the same type of the Node's key variable;
   *
  **/
  void insert(int const &value)
  {
    pointer current = _root;
    pointer previous = _nill;
    pointer newNode = new Node(value);

    while (current != _nill)
    {
      previous = current;
      current = value > current->key ? current->right : current->left;
    }
    newNode->parent = previous;

    if (previous == _nill)
      _root = newNode;
    else if (newNode->key < previous->key)
      previous->left = newNode;
    else
      previous->right = newNode;
    newNode->left = _nill;
    newNode->right = _nill;
    insertFixup(newNode);
  }

  // bool search(int const &key) const
  // {
  //   pointer current = _root;
  //
  //   while (current != _nill && current->key != key)
  //     current = key > current->key ? current->right : current->left;
  //   return current != _nill;
  // }

  void deleteKey(int const &key)
  {
    pointer toDelete;

    toDelete = search(key);
    _delete(toDelete);
    delete toDelete;
  }

  void printTree() const { printHelper(_root, "", true); }

private:

  /**
   * Structure used as Node for the Red-Black Tree.
  **/
  struct Node
  {
    typedef Node* pointer;

    pointer parent;
    pointer left;
    pointer right;
    int const key;
    unsigned int color:1;

    Node(int const &_key, unsigned int const &color = red)
      : parent(0), left(0), right(0), key(_key), color(color) {}
  };

  typedef Node::pointer pointer;

  // private attributes
  pointer const _nill;
  pointer _root;

  pointer search(int const &key)
  {
    pointer current = _root;

    while (current != _nill && current->key != key)
      current = key > current->key ? current->right : current->left;
    return current;
  }

  void _delete(pointer z)
  {
    pointer sucessorSubTree;
    pointer sucessor = z;
    unsigned int original_color = sucessor->color;

    if (z->left == _nill)
    {
      sucessorSubTree = z->right;
      transplant(z, z->right);
    }
    else if (z->right == _nill)
    {
      sucessorSubTree = z->left;
      transplant(z, z->left);
    }
    else
    {
      sucessor = minimum(z->right);
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
    if (from->parent == _nill)
      _root = to;
    else if (from == from->parent->left)
      from->parent->left = to;
    else
      from->parent->right = to;
    to->parent = from->parent;
  }

  pointer minimum(pointer subTreeRoot)
  {
    while (subTreeRoot->left != _nill)
      subTreeRoot = subTreeRoot->left;

    return subTreeRoot;
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

    if (rightSubTree->left != _nill)
      rightSubTree->left->parent = a;

    rightSubTree->parent = a->parent;

    if (a->parent == _nill)
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

    if (leftSubTree->right != _nill)
      leftSubTree->right->parent = a;

    leftSubTree->parent = a->parent;

    if (a->parent == _nill)
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
    if (root != _nill)
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

// Initialize RBTree's non-members atributes
unsigned int const RBTree::red = 1ul;
unsigned int const RBTree::black = 0ul;
} // namespace end

#endif // !RB_TREE_HPP
