/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseIterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:29:35 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/01/18 00:06:19 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSERITERATOR_HPP
#define REVERSERITERATOR_HPP

#include "base_iterator.hpp"
#include "NormalIterator.hpp"

namespace ft
{
  template<typename Iter>
  class ReverseIterator : public ft::Iterator<
                          typename ft::IteratorTraits<Iter>::iteratorCategory,
                          typename ft::IteratorTraits<Iter>::valueType,
                          typename ft::IteratorTraits<Iter>::differenceType,
                          typename ft::IteratorTraits<Iter>::pointer,
                          typename ft::IteratorTraits<Iter>::reference
                          >
  {
    private:
      Iter current;

    public:
      typedef typename ft::IteratorTraits<Iter>::valueType valueType;
      typedef typename ft::IteratorTraits<Iter>::iteratorCategory iteratorCategory;
      typedef typename ft::IteratorTraits<Iter>::differenceType differenceType;
      typedef typename ft::IteratorTraits<Iter>::pointer pointer;
      typedef typename ft::IteratorTraits<Iter>::reference reference;

      ReverseIterator() {}

      template<typename OtherIter>
      ReverseIterator(ReverseIterator<OtherIter> const &other) : current(other.base()) {}

      ReverseIterator(ReverseIterator const &other) : current(other.current) {}

      explicit ReverseIterator(Iter any) : current(any) {}

      Iter base() { return current; }

      //Operators
      reference operator*() { Iter tmp = current; return *--tmp; }
      pointer operator->() { return &(operator*()); }
      reference operator[](differenceType size) const {
        return *(*this + size);
      }
      ReverseIterator& operator++() { --current; return *this; }
      ReverseIterator& operator--() { ++current; return *this; }
      ReverseIterator operator++(int) {
        return ReverseIterator(current--);
      }
      ReverseIterator operator--(int) {
        return ReverseIterator(current++);
      }

      ReverseIterator operator+(differenceType size) const {
        return ReverseIterator(current - size);
      }

      ReverseIterator operator-(differenceType size) const {
        return ReverseIterator(current + size);
      }

      ReverseIterator& operator+=(differenceType size) {
        current -= size;
        return *this;
      }

      ReverseIterator& operator-=(differenceType size) {
        current += size;
        return *this;
      }
  };

  template<typename Iterator>
    inline bool operator==(
        ReverseIterator<Iterator> const &lhs,
        ReverseIterator<Iterator> const &rhs) {
      return lhs.base() == rhs.base();
    }

  template<typename Iterator>
    inline bool operator>(
        ReverseIterator<Iterator> const &lhs,
        ReverseIterator<Iterator> const &rhs) {
      return lhs.base() > rhs.base();
    }

  template<typename Iterator>
    inline bool operator!=(
        ReverseIterator<Iterator> const &lhs,
        ReverseIterator<Iterator> const &rhs) {
      return !(lhs == rhs);
    }

  template<typename Iterator>
    inline bool operator<(
        ReverseIterator<Iterator> const &lhs,
        ReverseIterator<Iterator> const &rhs) {
      return rhs > lhs;
    }

  template<typename Iterator>
    inline bool operator>=(
        ReverseIterator<Iterator> const &lhs,
        ReverseIterator<Iterator> const &rhs) {
      return !(rhs > lhs);
    }

  template<typename Iterator>
    inline bool operator<=(
        ReverseIterator<Iterator> const &lhs,
        ReverseIterator<Iterator> const &rhs) {
      return !(lhs > rhs);
    }

  template<typename Iterator>
    typename ReverseIterator<Iterator>::differenceType
    operator+(
        ReverseIterator<Iterator> const &lhs,
        typename ReverseIterator<Iterator>::differenceType size) {
      return ReverseIterator<Iterator>(lhs.base() - size);
    }

  template<typename IteratorL, typename IteratorR>
    typename ReverseIterator<IteratorL>::differenceType
    operator-(
        ReverseIterator<IteratorL> const &lhs,
        ReverseIterator<IteratorR> const &rhs) {
      return lhs.base() - rhs.base();
    }
}

#endif // !REVERSERITERATOR_HPP
