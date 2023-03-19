/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:22:58 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/03/18 13:55:11 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "RBTree.hpp"
#include "utility.hpp"
#include <cstddef>

namespace ft
{

template <
  typename Key,
  typename T,
  typename Compare = std::less<Key>,
  typename Alloc = std::allocator<ft::pair<Key const, T> >
>
class map
{
public:
  typedef Key                                       key_type;
  typedef T                                         mapped_type;
  typedef ft::pair<Key const, T>                    value_type;
  typedef std::size_t                               size_type;
  typedef std::ptrdiff_t                            difference_type;
  typedef Compare                                   key_compare;

  typedef Alloc                                     allocator_type;
  typedef value_type &                              reference;
  typedef value_type const &                        const_reference;
  typedef typename Alloc::pointer                   pointer;
  typedef typename Alloc::const_pointer             const_pointer;

  class value_compare;

protected:


  template<typename U>
    struct getFirst;

  typedef
  internals::RBTree<
    key_type, value_type, getFirst<value_type>, key_compare, allocator_type
  > RBTree;

  typedef map<key_type, mapped_type, key_compare, allocator_type> Self;

  RBTree tree;

public:

  typedef typename RBTree::iterator               iterator;
  typedef typename RBTree::const_iterator         const_iterator;
  typedef typename RBTree::reverse_iterator       reverse_iterator;
  typedef typename RBTree::const_reverse_iterator const_reverse_iterator;

  map() {}

  explicit map(key_compare const &comp, allocator_type const &alloc)
    : tree(comp, alloc) {}

  template<typename II>
    map(II first, II last,
      key_compare const &comp = key_compare(),
      allocator_type const &alloc = allocator_type()) : tree(comp, alloc)
    {
      tree.insert(first, last);
    }

  map(Self const &other) : tree(other.tree) {}

  ~map() {}

  Self & operator=(Self const &other) { tree = other.tree; }

  iterator begin() { return tree.begin(); }
  const_iterator begin() const { return tree.begin(); }
  iterator end() { return tree.end(); }
  const_iterator end() const { return tree.end(); }
  reverse_iterator rbegin() { return tree.rbegin(); }
  const_reverse_iterator rbegin() const { return tree.rbegin(); }
  reverse_iterator rend() { return tree.rend(); }
  const_reverse_iterator rend() const { return tree.rend(); }

  bool empty() const { return tree.empty(); }
  size_type size() const { return tree.size(); }
  size_type max_size() const { return tree.max_size(); }

  mapped_type &operator[](key_type const &key) 
  {
    return (*(insert(make_pair(key, mapped_type())).first)).second;
  }

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

  void erase(iterator pos) { tree.erase(pos); }
  size_type erase(key_type const &key) { return tree.erase(key); }
  void erase(iterator first, iterator last) { tree.erase(first, last); }

  void swap(Self &other) { tree.swap(other.tree); }

  void clear() { tree.clear(); }

  size_type count(key_type const &key) const { return tree.count(key); }

  iterator find(key_type const &key) { return tree.find(key); }
  const_iterator find(key_type const &key) const { return tree.find(key); }

  iterator lower_bound(key_type const &key) { return tree.lower_bound(key); }
  const_iterator lower_bound(key_type const &key) const
  {
    return tree.lower_bound(key);
  }

  iterator upper_bound(key_type const &key)
  {
    return tree.upper_bound(key);
  }

  const_iterator upper_bound(key_type const &key) const
  {
    return tree.upper_bound(key);
  }

  ft::pair<iterator, iterator> equal_range(key_type const &key)
  {
    return tree.equal_range(key);
  }

  ft::pair<const_iterator, const_iterator>
    equal_range(key_type const &key) const
  {
    return tree.equal_range(key);
  }

  allocator_type get_allocator() const { return allocator_type(); }

  key_compare key_comp() const { return key_compare(); }

  value_compare value_comp() const { return value_compare(key_compare()); }

};

template<typename Key, typename T, typename Comp, typename Alloc>
class map<Key, T, Comp, Alloc>::value_compare
  : public std::binary_function<value_type, value_type, bool>
{
  friend class map<Key, T, Comp, Alloc>;

protected:
  key_compare comp;
  value_compare(key_compare const &cmp) : comp(cmp) {}

public:
  bool operator()(value_type const &lhs, value_type const &rhs) const
  {
    return comp(lhs.first, rhs.first);
  }
};


template<typename Key, typename T, typename Comp, typename Alloc>
template<typename U>
struct map<Key, T, Comp, Alloc>::getFirst
{
  typename U::first_type const &operator()(U const &element) const
  {
    return element.first;
  }
};

} // end of namespace

#endif // !MAP_HPP
