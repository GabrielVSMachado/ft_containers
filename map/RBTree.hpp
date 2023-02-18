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

namespace internals
{
  class RBTree
  {

  private:

    static unsigned int const red = 1;
    static unsigned int const black = 0;

    struct Node
    {
      typedef Node* pointer;

      pointer parent;
      pointer left;
      pointer right;
      int const key;
      unsigned int color:1;

      Node(int const &value, Node* const & nill)
        : parent(nill), left(nill), right(nill), key(value), color(black) {}
    };

    typedef Node::pointer pointer;

    pointer const _nill;
    pointer _root;


  public:
    RBTree() : _nill(new Node(0, 0)), _root(_nill) {}

    void insert(int const &value)
    {
      pointer current = _root;
      pointer previous = _root;
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
  }; // end of RBTree
} // namespace end

#endif // !RB_TREE_HPP
