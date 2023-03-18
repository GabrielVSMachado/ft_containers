/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:15:06 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/03/18 15:49:14 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
#include <cstddef>

template<typename T, typename Container = ft::vector<T> >
class stack
{
protected:
  Container ctrn;

public:
  typedef T value_type;
  typedef Container container_type;
  typedef typename container_type::size_type size_type;
  typedef typename container_type::reference reference;
  typedef typename container_type::const_reference const_reference;

  explicit stack(container_type const &__c = container_type()) : ctrn(__c) {}

  bool empty() const { return ctrn.empty(); }
  size_type size() const { return ctrn.size(); }

  value_type &top() { return ctrn.back(); }
  value_type const &top() const { return ctrn.back(); }
  void push(value_type const &value) { ctrn.push_back(value); }
  void pop() { ctrn.pop_back(); }

  bool operator==(stack<T, Container> const &rhs) { return ctrn == rhs.ctrn; }
  bool operator!=(stack<T, Container> const &rhs) { return ctrn != rhs.ctrn; }
  bool operator<(stack<T, Container> const &rhs) { return ctrn < rhs.ctrn; }
  bool operator<=(stack<T, Container> const &rhs) { return ctrn <= rhs.ctrn; }
  bool operator>(stack<T, Container> const &rhs) { return ctrn > rhs.ctrn; }
  bool operator>=(stack<T, Container> const &rhs) { return ctrn >= rhs.ctrn; }
};

#endif // !STACK_HPP
