/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 21:07:56 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/01/25 21:27:38 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

namespace ft
{
  template<typename InputIt1, typename InputIt2>
    bool equal(InputIt1 first, InputIt1 last, InputIt2 to_compare)
    {
      for (; first != last; ++first, ++to_compare)
      {
        if (!(*first == *to_compare))
          return false;
      }
      return true;
    }

  template<typename InputIt1, typename InputIt2, typename fn>
    bool equal(InputIt1 first, InputIt1 last, InputIt2 to_compare, fn f)
    {
      for (; first != last; ++first, ++to_compare)
      {
        if (!f(*first, *to_compare))
          return false;
      }
      return true;
    }

  template<class II1, class II2>
  bool lexicographical_compare(II1 first1, II1 last1, II2 first2, II2 last2)
  {
    while (first1 != last1)
    {
      if (first2 == last2 || *first2 < *first1)
        return false;
      else if (*first1 < *first2)
        return true;
      ++first1;
      ++first2;
    }
    return first2 != last2;
  }
}

#endif // !ALGORITHMS_HPP
