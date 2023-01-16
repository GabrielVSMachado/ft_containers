/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NormalIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:57:38 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/01/10 23:44:33 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base_iterator.hpp"

namespace internals
{
  template<typename Iterator, typename Container>
    class NormalIterator {

    protected:
      Iterator current;

    public:
      typedef typename ft::IteratorTraits<Iterator>::iteratorCategory
                                                              iteratorCategory;

      typedef typename ft::IteratorTraits<Iterator>::differenceType
                                                                differenceType;

      typedef typename ft::IteratorTraits<Iterator>::valueType valueType;
      typedef typename ft::IteratorTraits<Iterator>::pointer pointer;
      typedef typename ft::IteratorTraits<Iterator>::reference reference;

      //Constructors
      NormalIterator() : current(Iterator()) {}

      explicit NormalIterator(Iterator const &other) : current(other) {}

      template<typename Iter>
        inline NormalIterator(
            NormalIterator<Iter, Container> const &other)
        : current(other.base()) {}

      //Base
      Iterator const& base() { return current; }

      //Operators
      reference operator*() const { return *current; }
      pointer operator->() const { return current; }
      NormalIterator& operator++() { return *(++current); }
      NormalIterator& operator++(int) { return NormalIterator(current++); }
      NormalIterator& operator--() { return *(--current); }
      NormalIterator& operator--(int) { return NormalIterator(current--); }

      NormalIterator& operator[](differenceType const &index) {
        return current[index];
      }

      NormalIterator& operator+=(differenceType const &diff) {
        current += diff;
        return *this;
      }

      NormalIterator& operator-=(differenceType const &diff) {
        current -= diff;
        return *this;
      }

      NormalIterator& operator+(differenceType const &diff) const {
        return NormalIterator(current + diff);
      }

      NormalIterator& operator-(differenceType const &diff) const {
        return NormalIterator(current - diff);
      }
    };

  // boolean operator to Iterator of same type

  template<typename Iterator, typename Container>
    NormalIterator<Iterator, Container>&
    operator==(NormalIterator<Iterator, Container> const &lhs,
              NormalIterator<Iterator, Container> const &rhs) {
      return lhs.base() == rhs.base();
    }

  template<typename Iterator, typename Container>
    inline bool operator>(NormalIterator<Iterator, Container> const &lhs,
              NormalIterator<Iterator, Container> const &rhs) {
      return lhs.base() > rhs.base();
    }

  template<typename Iterator, typename Container>
    inline bool operator!=(
        NormalIterator<Iterator, Container> const &lhs,
        NormalIterator<Iterator, Container> const &rhs) {
      return lhs.base() != rhs.base();
    }

  template<typename Iterator, typename Container>
    inline bool operator<(
        NormalIterator<Iterator, Container> const &lhs,
        NormalIterator<Iterator, Container> const &rhs) {
      return lhs.base() < rhs.base();
    }

  template<typename Iterator, typename Container>
    inline bool operator<=(
        NormalIterator<Iterator, Container> const &lhs,
        NormalIterator<Iterator, Container> const &rhs) {
      return lhs.base() <= rhs.base();
    }

  template<typename Iterator, typename Container>
    inline bool operator>=(
        NormalIterator<Iterator, Container> const &lhs,
        NormalIterator<Iterator, Container> const &rhs) {
      return lhs.base() >= rhs.base();
    }

  // boolean operator between iterators of differente types
  
  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator==(
        NormalIterator<LIterator, Container> const &lhs,
        NormalIterator<RIterator, Container> const &rhs) {
      return lhs.base() == rhs.base();
    }

  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator!=(
        NormalIterator<LIterator, Container> const &lhs,
        NormalIterator<RIterator, Container> const &rhs) {
      return lhs.base() != rhs.base();
    }

  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator>(
        NormalIterator<LIterator, Container> const &lhs,
        NormalIterator<RIterator, Container> const &rhs) {
      return lhs.base() > rhs.base();
    }
  
  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator<(
        NormalIterator<LIterator, Container> const &lhs,
        NormalIterator<RIterator, Container> const &rhs) {
      return lhs.base() < rhs.base();
    }

  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator<=(
        NormalIterator<LIterator, Container> const &lhs,
        NormalIterator<RIterator, Container> const &rhs) {
      return lhs.base() <= rhs.base();
    }

  template<typename LIterator, typename RIterator, typename Container>
    inline bool operator>=(
        NormalIterator<LIterator, Container> const &lhs,
        NormalIterator<RIterator, Container> const &rhs) {
      return lhs.base() >= rhs.base();
    }
}
