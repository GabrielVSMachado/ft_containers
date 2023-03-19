/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:54:00 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/03/18 18:57:58 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include "RBTree.hpp"

namespace ft
{

template<
  typename T,
  typename Compare = std::less<T>,
  typename Alloc = std::allocator<T>
>
class set
{
public:
  typedef T                                         key_type;
  typedef T                                         value_type;
  typedef Compare                                   key_compare;
  typedef Compare                                   value_compare;

  typedef typename Alloc::reference        reference;
  typedef typename Alloc::const_reference  const_reference;
  typedef typename Alloc::pointer          pointer;
  typedef typename Alloc::const_pointer    const_pointer;

protected:
  template<typename U>
  struct getValue { U const &operator()(U const &value) const { return value; } };

  typedef
  internals::RBTree<key_type, value_type, getValue<value_type>, key_compare, Alloc>
  RBTree;

  RBTree tree;

  typedef set<T, Compare, Alloc> Self;

public:

  typedef typename RBTree::const_iterator         iterator;
  typedef typename RBTree::const_iterator         const_iterator;
  typedef typename RBTree::reverse_iterator       reverse_iterator;
  typedef typename RBTree::const_reverse_iterator const_reverse_iterator;
  typedef typename RBTree::allocator_type         allocator_type;
  typedef typename RBTree::size_type              size_type;
  typedef typename RBTree::difference_type        difference_type;

  explicit set(key_compare const &cmp = key_compare(),
      allocator_type const &alloc = allocator_type())
    : tree(cmp, alloc) {}

  template<typename II>
    set(II first, II last,
        key_compare const &cmp = key_compare(),
        allocator_type const &alloc = allocator_type()) : tree(cmp, alloc)
  {
    tree.insert(first, last);
  }

  set(Self const &other) : tree(other.tree) {}

  ~set() {}

  Self &operator=(Self const &other)
  {
    tree = other.tree;
    return *this;
  }

  iterator begin() { return tree.begin(); }
  const_iterator begin() const { return tree.begin(); }
  iterator end() { return tree.end(); }
  const_iterator end() const { return tree.end(); }

  iterator rbegin() { return tree.rbegin(); }
  const_iterator rbegin() const { return tree.rbegin(); }
  iterator rend() { return tree.rend(); }
  const_iterator rend() const { return tree.rend(); }

  bool empty() const { return tree.empty(); }
  size_type size() const { return tree.size(); }
  size_type max_size() const { return tree.max_size(); }

  ft::pair<iterator, bool> insert(value_type const &value)
  {
    return tree.insert(value);
  }

  iterator insert(iterator position, value_type const &value)
  {
    return tree.insert(position, value);
  }

  template<typename II>
    void insert(II first, II last) { tree.insert(first, last); }

  void erase(iterator position) { tree.erase(position); }
  size_type erase(value_type const &value) { return tree.erase(value); }
  void erase(iterator first, iterator last) { tree.erase(first, last); }

  void swap(Self &other) { tree.swap(other.tree); }

  void clear() { tree.clear(); }


  iterator find(key_type const &key) const { return tree.find(key); }
  size_type count(value_type const &value) const { return tree.count(value); }

  iterator lower_bound(value_type const &value) const
  {
    return tree.lower_bound(value);
  }

  iterator upper_bound(value_type const &value) const
  {
    return tree.upper_bound(value);
  }

  ft::pair<iterator, iterator> equal_range(value_type const &value) const
  {
    return tree.equal_range(value);
  }

  allocator_type get_allocator() { return allocator_type(); }
  key_compare key_comp() { return key_compare(); }
  value_compare value_comp() const { return value_compare(); }

  inline bool operator==(Self const &rhs) const { return tree == rhs.tree; }
  inline bool operator<(Self const &rhs) const { return tree < rhs.tree; }
  inline bool operator!=(Self const &rhs) const { return !(*this == rhs); }
  inline bool operator>(Self const &rhs) const { return rhs < *this; }
  inline bool operator>=(Self const &rhs) const { return !(*this < rhs); }
  inline bool operator<=(Self const &rhs) const { return !(rhs < *this); }
};
}

#endif // !SET_HPP
