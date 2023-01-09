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
  struct InputIteratorTag {};

  struct OutputIteratorTag {};

  struct ForwardIteratorTag : public InputIteratorTag {};

  struct BidirectionalIteratorTag : public ForwardIteratorTag {};

  struct RandomAccessIteratorTag : public BidirectionalIteratorTag {};


  template<
    typename Category,
    typename T,
    typename Distance = std::ptrdiff_t,
    typename Pointer = T*,
    typename Reference = T&
  >
    struct Iterator
    {
      typedef Category iteratorCategory;
      typedef T valueType;
      typedef Distance differenceType;
      typedef Pointer pointer;
      typedef Reference reference;
    };

  template<typename Iter>
    struct IteratorTraits
    {
      typedef typename Iter::iteratorCategory iteratorCategory;
      typedef typename Iter::valueType valueType;
      typedef typename Iter::differenceType differenceType;
      typedef typename Iter::pointer pointer;
      typedef typename Iter::reference reference;
    };

  template<typename T>
    struct IteratorTraits<T*>
    {
      typedef RandomAccessIteratorTag iteratorCategory;
      typedef T valueType;
      typedef std::ptrdiff_t differenceType;
      typedef T* pointer;
      typedef T& reference;
    };

  template<typename T>
    struct IteratorTraits<T const *>
    {
      typedef RandomAccessIteratorTag iteratorCategory;
      typedef T valueType;
      typedef std::ptrdiff_t differenceType;
      typedef T* pointer;
      typedef T& reference;
    };
}

#endif
