/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:23:55 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/01/21 18:12:54 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft
{
  template<typename T1, typename T2>
    struct pair
    {
      typedef T1 first_type;
      typedef T2 second_type;

      first_type first;
      second_type second;

      pair() {}

      pair(first_type const &f, second_type const &s) : first(f), second(s) {}

      template<typename U1, typename U2>
        pair(ft::pair<U1, U2> const &other)
        : first(other.first), second(other.second) {}

      pair<T1, T2>& operator=(pair<T1, T2> const &other) {
        first = other.first;
        second = other.second;
        return *this;
      }
    };

  template<typename T1, typename T2>
    pair<T1, T2> make_pair(T1 first, T2 second) {
      return pair<T1, T2>(first, second);
    }

  template<typename T1, typename T2>
    bool operator==(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs) {
      return lhs.first == rhs.first && lhs.second == rhs.second;
    }
  
  template<typename T1, typename T2>
    bool operator<(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs) {
      return lhs.first < rhs.first && lhs.second < rhs.second;
    }

  template<typename T1, typename T2>
    bool operator!=(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs) {
      return !(lhs == rhs);
    }

  template<typename T1, typename T2>
    bool operator>(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs) {
      return rhs < lhs;
    }

  template<typename T1, typename T2>
    bool operator<=(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs) {
      return !(lhs > rhs);
    }

  template<typename T1, typename T2>
    bool operator>=(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs) {
      return !(lhs < rhs);
    }

  template<typename T>
    bool cmp_less(T const &a, T const &b) { return a < b; }
}

#endif // !UTILITY_HPP
