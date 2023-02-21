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
public:
  static unsigned int const red;
  static unsigned int const black;

  RBTree() : _nill(new Node(0, 0, black)), _root(_nill) {}

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
    pointer newNode = new Node(value, _nill);

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
    // TODO: FIXUP_INSERT
  }

  bool search(int const &key)
  {
    pointer current = _root;

    while (current != _nill && current->key != key)
      current = key > current->key ? current->right : current->left;
    return current != _nill;
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

    Node(int const &value, pointer const & nill, unsigned int const &color = red)
      : parent(nill), left(nill), right(nill), key(value), color(color) {}
  };

  typedef Node::pointer pointer;

  // private attributes
  pointer const _nill;
  pointer _root;


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
