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
#define NormalIterator_HPP

#include "base_iterator.hpp"

namespace internals
{
  template<typename Iterator, typename Container>
    class normal_iterator
    {

    protected:
      Iterator current;

    public:
      typedef typename ft::iterator_traits<Iterator>::iteratorCategory
                                                              iteratorCategory;

      typedef typename ft::iterator_traits<Iterator>::differenceType
                                                                differenceType;

      typedef typename ft::iterator_traits<Iterator>::valueType valueType;
      typedef typename ft::iterator_traits<Iterator>::pointer pointer;
      typedef typename ft::iterator_traits<Iterator>::reference reference;

      //Constructors
      normal_iterator() : current(Iterator()) {}

      explicit normal_iterator(Iterator const &other) : current(other) {}

      template<typename Iter>
        inline normal_iterator(
            normal_iterator<Iter, Container> const &other)
        : current(other.base()) {}

      //Base
      Iterator const& base() { return current; }

      //Operators
      reference operator*() { return *current; }
      pointer operator->() const { return current; }
      normal_iterator& operator++() { return *(++current); }
      normal_iterator operator++(int) const { return current++; }
      normal_iterator& operator--() { return *(--current); }
      normal_iterator operator--(int) const { return current--; }

      normal_iterator& operator[](differenceType const &index) const {
        return current[index];
      }

      normal_iterator& operator+=(differenceType const &diff) {
        current += diff;
        return *this;
      }

      normal_iterator& operator-=(differenceType const &diff) {
        current -= diff;
        return *this;
      }

      normal_iterator& operator+(differenceType const &diff) const {
        return normal_iterator(current + diff);
      }

      normal_iterator& operator-(differenceType const &diff) const {
        return normal_iterator(current - diff);
      }
    }; // finish normal_iterator

  // boolean operator to Iterator of same type

  template<typename Iterator, typename Container>
    normal_iterator<Iterator, Container>&
    operator==(normal_iterator<Iterator, Container> const &lhs,
              normal_iterator<Iterator, Container> const &rhs) {
      return lhs.base() == rhs.base();
    }

  template<typename Iterator, typename Container>
    inline bool operator>(normal_iterator<Iterator, Container> const &lhs,
              normal_iterator<Iterator, Container> const &rhs) {
      return lhs.base() > rhs.base();
    }

  template<typename Iterator, typename Container>
    inline bool operator!=(
        normal_iterator<Iterator, Container> const &lhs,
        normal_iterator<Iterator, Container> const &rhs) {
      return lhs.base() != rhs.base();
    }

  template<typename Iterator, typename Container>
    inline bool operator<(
        normal_iterator<Iterator, Container> const &lhs,
        normal_iterator<Iterator, Container> const &rhs) {
      return lhs.base() < rhs.base();
    }

  template<typename Iterator, typename Container>
    inline bool operator<=(
        normal_iterator<Iterator, Container> const &lhs,
        normal_iterator<Iterator, Container> const &rhs) {
      return lhs.base() <= rhs.base();
    }

  template<typename Iterator, typename Container>
    inline bool operator>=(
        normal_iterator<Iterator, Container> const &lhs,
        normal_iterator<Iterator, Container> const &rhs) {
      return lhs.base() >= rhs.base();
    }

  // boolean operator between iterators of differente types
  
  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator==(
        normal_iterator<LIterator, Container> const &lhs,
        normal_iterator<RIterator, Container> const &rhs) {
      return lhs.base() == rhs.base();
    }

  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator!=(
        normal_iterator<LIterator, Container> const &lhs,
        normal_iterator<RIterator, Container> const &rhs) {
      return lhs.base() != rhs.base();
    }

  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator>(
        normal_iterator<LIterator, Container> const &lhs,
        normal_iterator<RIterator, Container> const &rhs) {
      return lhs.base() > rhs.base();
    }
  
  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator<(
        normal_iterator<LIterator, Container> const &lhs,
        normal_iterator<RIterator, Container> const &rhs) {
      return lhs.base() < rhs.base();
    }

  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator<=(
        normal_iterator<LIterator, Container> const &lhs,
        normal_iterator<RIterator, Container> const &rhs) {
      return lhs.base() <= rhs.base();
    }

  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator>=(
        normal_iterator<LIterator, Container> const &lhs,
        normal_iterator<RIterator, Container> const &rhs) {
      return lhs.base() >= rhs.base();
    }
}

#endif
