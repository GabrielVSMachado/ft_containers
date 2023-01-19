/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:05:46 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/01/09 00:06:22 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_ITERATOR_HPP
#define BASE_ITERATOR_HPP

#include <cstddef>

namespace ft
{
  struct input_iterator_tag {};

  struct output_iterator_tag {};

  struct forward_iterator_tag : public input_iterator_tag {};

  struct bidirectional_iterator_tag : public forward_iterator_tag {};

  struct random_access_iterator_tag : public bidirectional_iterator_tag {};


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
      typedef random_access_iterator_tag iterator_category;
      typedef T value_type;
      typedef std::ptrdiff_t difference_type;
      typedef T* pointer;
      typedef T& reference;
    };

  template<typename T>
    struct iterator_traits<T const *>
    {
      typedef random_access_iterator_tag iterator_category;
      typedef T value_type;
      typedef std::ptrdiff_t difference_type;
      typedef T* pointer;
      typedef T& reference;
    };
}

#endif
