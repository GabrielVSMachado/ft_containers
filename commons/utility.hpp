/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:23:55 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/01/08 21:54:46 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft
{
  template<typename T1, typename T2>
    struct Pair
    {
      typedef T1 firstType;
      typedef T2 secondType;

      firstType first;
      secondType second;

      Pair() {}

      Pair(firstType const &f, secondType const &s) {
        first = f;
        second = s;
      }

      template<typename U1, typename U2>
        Pair(ft::Pair<U1, U2> const &other) {
          *this = other;
        }

      Pair<T1, T2>& operator=(Pair<T1, T2> const &other) {
        first = other.first;
        second = other.second;
        return *this;
      }
    };

  template<typename T1, typename T2>
    Pair<T1, T2> makePair(T1 first, T2 second) {
      return Pair<T1, T2>(first, second);
    }

  template<typename T1, typename T2>
    bool operator==(Pair<T1, T2> const &lhs, Pair<T1, T2> const &rhs) {
      return lhs.first == rhs.first && lhs.second == rhs.second;
    }
  
  template<typename T1, typename T2>
    bool operator<(Pair<T1, T2> const &lhs, Pair<T1, T2> const &rhs) {
      return lhs.first < rhs.first && lhs.second < rhs.second;
    }

  template<typename T1, typename T2>
    bool operator!=(Pair<T1, T2> const &lhs, Pair<T1, T2> const &rhs) {
      return !(lhs == rhs);
    }

  template<typename T1, typename T2>
    bool operator>(Pair<T1, T2> const &lhs, Pair<T1, T2> const &rhs) {
      return rhs < lhs;
    }

  template<typename T1, typename T2>
    bool operator<=(Pair<T1, T2> const &lhs, Pair<T1, T2> const &rhs) {
      return !(lhs > rhs);
    }

  template<typename T1, typename T2>
    bool operator>=(Pair<T1, T2> const &lhs, Pair<T1, T2> const &rhs) {
      return !(lhs < rhs);
    }
}

#endif // !UTILITY_HPP
