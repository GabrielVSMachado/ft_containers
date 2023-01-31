/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NormalIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:57:38 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/01/17 22:58:54 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef NORMALITERATOR_HPP
#define NORMALITERATOR_HPP

#include "iterator.hpp"

namespace internals
{
  template<typename Iterator, typename Container>
    class normal_iterator
    {

    protected:
      Iterator current;

    public:
      typedef typename ft::iterator_traits<Iterator>::iterator_category
                                                              iterator_category;

      typedef typename ft::iterator_traits<Iterator>::difference_type
                                                                difference_type;

      typedef typename ft::iterator_traits<Iterator>::value_type value_type;
      typedef typename ft::iterator_traits<Iterator>::pointer pointer;
      typedef typename ft::iterator_traits<Iterator>::reference reference;

      //Constructors
      normal_iterator() : current(Iterator()) {}

      explicit normal_iterator(Iterator const &other) : current(other) {}

      template<typename Iter>
        inline normal_iterator(normal_iterator<Iter, Container> const &other)
        : current(other.base()) {}

      //Base
      Iterator const& base() const { return current; }

      //Operators
      reference operator*() { return *current; }
      pointer operator->() const { return current; }
      normal_iterator& operator++() { ++current; return *this; }
      normal_iterator operator++(int) { return normal_iterator(current++); }
      normal_iterator& operator--() { --current; return *this; }
      normal_iterator operator--(int) { return normal_iterator(current--); }

      reference operator[](difference_type const &index) const
      {
        return current[index];
      }

      normal_iterator& operator+=(difference_type const &diff)
      {
        current += diff;
        return *this;
      }

      normal_iterator& operator-=(difference_type const &diff)
      {
        current -= diff;
        return *this;
      }

      normal_iterator operator+(difference_type const &diff) const
      {
        return normal_iterator(current + diff);
      }

      normal_iterator operator-(difference_type const &diff) const
      {
        return normal_iterator(current - diff);
      }
    }; // finish normal_iterator

  // boolean operator to Iterator of same type

  template<typename Iterator, typename Container>
    inline bool operator==(
        normal_iterator<Iterator, Container> const &lhs,
        normal_iterator<Iterator, Container> const &rhs)
    {
      return lhs.base() == rhs.base();
    }

  template<typename Iterator, typename Container>
    inline bool operator>(normal_iterator<Iterator, Container> const &lhs,
              normal_iterator<Iterator, Container> const &rhs)
    {
      return lhs.base() > rhs.base();
    }

  template<typename Iterator, typename Container>
    inline bool operator!=(
        normal_iterator<Iterator, Container> const &lhs,
        normal_iterator<Iterator, Container> const &rhs)
    {
      return lhs.base() != rhs.base();
    }

  template<typename Iterator, typename Container>
    inline bool operator<(
        normal_iterator<Iterator, Container> const &lhs,
        normal_iterator<Iterator, Container> const &rhs)
    {
      return lhs.base() < rhs.base();
    }

  template<typename Iterator, typename Container>
    inline bool operator<=(
        normal_iterator<Iterator, Container> const &lhs,
        normal_iterator<Iterator, Container> const &rhs)
    {
      return lhs.base() <= rhs.base();
    }

  template<typename Iterator, typename Container>
    inline bool operator>=(
        normal_iterator<Iterator, Container> const &lhs,
        normal_iterator<Iterator, Container> const &rhs)
    {
      return lhs.base() >= rhs.base();
    }

  // boolean operator between iterators of differente types
  
  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator==(
        normal_iterator<LIterator, Container> const &lhs,
        normal_iterator<RIterator, Container> const &rhs)
    {
      return lhs.base() == rhs.base();
    }

  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator!=(
        normal_iterator<LIterator, Container> const &lhs,
        normal_iterator<RIterator, Container> const &rhs)
    {
      return lhs.base() != rhs.base();
    }

  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator>(
        normal_iterator<LIterator, Container> const &lhs,
        normal_iterator<RIterator, Container> const &rhs)
    {
      return lhs.base() > rhs.base();
    }
  
  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator<(
        normal_iterator<LIterator, Container> const &lhs,
        normal_iterator<RIterator, Container> const &rhs)
    {
      return lhs.base() < rhs.base();
    }

  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator<=(
        normal_iterator<LIterator, Container> const &lhs,
        normal_iterator<RIterator, Container> const &rhs)
    {
      return lhs.base() <= rhs.base();
    }

  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator>=(
        normal_iterator<LIterator, Container> const &lhs,
        normal_iterator<RIterator, Container> const &rhs)
    {
      return lhs.base() >= rhs.base();
    }

  template<typename LIterator, typename RIterator, typename Container>
    inline typename normal_iterator<LIterator, Container>::difference_type
    operator-(
        normal_iterator<LIterator, Container> const &lhs,
        normal_iterator<RIterator, Container> const &rhs)
    {
      return lhs.base() - rhs.base();
    }

  template<typename LIterator, typename Container>
    inline normal_iterator<LIterator, Container>
    operator+(
        normal_iterator<LIterator, Container> const &lhs,
        typename normal_iterator<LIterator, Container>::difference_type diff)
    {
      return normal_iterator<LIterator, Container>(lhs.base() + diff);
    }
}

#endif
