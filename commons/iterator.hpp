/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:08:59 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/01/25 21:47:43 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "type_traits.hpp"
#include <cstddef>

namespace ft
{
  template<
    typename Category,
    typename T,
    typename Distance = std::ptrdiff_t,
    typename Pointer = T*,
    typename Reference = T&
  >
    struct iterator
    {
      typedef Category iterator_category;
      typedef T value_type;
      typedef Distance difference_type;
      typedef Pointer pointer;
      typedef Reference reference;
    };

  template<typename Iter>
    struct iterator_traits
    {
      typedef typename Iter::iterator_category iterator_category;
      typedef typename Iter::value_type value_type;
      typedef typename Iter::difference_type difference_type;
      typedef typename Iter::pointer pointer;
      typedef typename Iter::reference reference;
    };

  template<typename T>
    struct iterator_traits<T*>
    {
      typedef std::random_access_iterator_tag iterator_category;
      typedef T value_type;
      typedef std::ptrdiff_t difference_type;
      typedef T* pointer;
      typedef T& reference;
    };

  template<typename T>
    struct iterator_traits<T const *>
    {
      typedef std::random_access_iterator_tag iterator_category;
      typedef T value_type;
      typedef std::ptrdiff_t difference_type;
      typedef T const * pointer;
      typedef T const & reference;
    };

  template<typename InputIt>
    typename ft::iterator_traits<InputIt>::difference_type
    calculate_distance(InputIt first, InputIt last, std::random_access_iterator_tag)
    {
      return last - first;
    }

  template<typename InputIt>
    typename ft::iterator_traits<InputIt>::difference_type
    calculate_distance(InputIt first, InputIt last, std::input_iterator_tag)
    {
      typename ft::iterator_traits<InputIt>::difference_type size;

      size = 0;
      while (first != last)
      {
        ++first;
        ++size;
      }
      return size;
    }

  template<typename InputIt>
    typename ft::iterator_traits<InputIt>::difference_type
    distance(InputIt first, InputIt last)
    {
      return calculate_distance(first, last,
              typename ft::iterator_traits<InputIt>::iterator_category()
            );
    }
}

#endif // !ITERATOR_HPP
