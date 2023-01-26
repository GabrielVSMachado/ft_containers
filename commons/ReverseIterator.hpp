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

#include "iterator.hpp"

namespace ft
{
  template<typename Iter>
  class reverse_iterator : public ft::iterator<
                          typename ft::iterator_traits<Iter>::iterator_category,
                          typename ft::iterator_traits<Iter>::value_type,
                          typename ft::iterator_traits<Iter>::difference_type,
                          typename ft::iterator_traits<Iter>::pointer,
                          typename ft::iterator_traits<Iter>::reference
                          >
  {
    protected:
      Iter current;

    public:
      typedef typename ft::iterator_traits<Iter>::value_type value_type;
      typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
      typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
      typedef typename ft::iterator_traits<Iter>::pointer pointer;
      typedef typename ft::iterator_traits<Iter>::reference reference;

      reverse_iterator() : current(0) {}

      template<typename OtherIter>
      reverse_iterator(reverse_iterator<OtherIter> const &other) : current(other.base()) {}

      reverse_iterator(reverse_iterator const &other) : current(other.current) {}

      explicit reverse_iterator(Iter const & any) : current(any) {}

      Iter base() { return current; }

      //Operators
      reference operator*() const { Iter tmp = current; return *--tmp; }
      pointer operator->() { return &(operator*()); }
      reference operator[](difference_type size) const {
        return *(*this + size);
      }
      reverse_iterator& operator++() { --current; return *this; }
      reverse_iterator& operator--() { ++current; return *this; }
      reverse_iterator operator++(int) const
      {
        return reverse_iterator(current--);
      }
      reverse_iterator operator--(int) const
      {
        return reverse_iterator(current++);
      }

      reverse_iterator operator+(difference_type size) const {
        return reverse_iterator(current - size);
      }

      reverse_iterator operator-(difference_type size) const {
        return reverse_iterator(current + size);
      }

      reverse_iterator& operator+=(difference_type size) {
        current -= size;
        return *this;
      }

      reverse_iterator& operator-=(difference_type size) {
        current += size;
        return *this;
      }
  };

  template<typename Iterator>
    inline bool operator==(
        reverse_iterator<Iterator> const &lhs,
        reverse_iterator<Iterator> const &rhs) {
      return lhs.base() == rhs.base();
    }

  template<typename Iterator>
    inline bool operator>(
        reverse_iterator<Iterator> const &lhs,
        reverse_iterator<Iterator> const &rhs) {
      return lhs.base() > rhs.base();
    }

  template<typename Iterator>
    inline bool operator!=(
        reverse_iterator<Iterator> const &lhs,
        reverse_iterator<Iterator> const &rhs) {
      return !(lhs == rhs);
    }

  template<typename Iterator>
    inline bool operator<(
        reverse_iterator<Iterator> const &lhs,
        reverse_iterator<Iterator> const &rhs) {
      return rhs > lhs;
    }

  template<typename Iterator>
    inline bool operator>=(
        reverse_iterator<Iterator> const &lhs,
        reverse_iterator<Iterator> const &rhs) {
      return !(rhs > lhs);
    }

  template<typename Iterator>
    inline bool operator<=(
        reverse_iterator<Iterator> const &lhs,
        reverse_iterator<Iterator> const &rhs) {
      return !(lhs > rhs);
    }

  template<typename Iterator>
    typename reverse_iterator<Iterator>::difference_type
    operator+(
        reverse_iterator<Iterator> const &lhs,
        typename reverse_iterator<Iterator>::difference_type size) {
      return reverse_iterator<Iterator>(lhs.base() - size);
    }

  template<typename IteratorL, typename IteratorR>
    typename reverse_iterator<IteratorL>::difference_type
    operator-(
        reverse_iterator<IteratorL> const &lhs,
        reverse_iterator<IteratorR> const &rhs) {
      return lhs.base() - rhs.base();
    }
}

#endif // !REVERSERITERATOR_HPP
