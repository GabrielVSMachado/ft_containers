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
}

#endif // !ALGORITHMS_HPP
