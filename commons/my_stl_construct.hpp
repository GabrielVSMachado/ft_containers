/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_stl_construct.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:49:18 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/01/21 18:14:46 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_STL_CONSTRUCT_HPP
#define MY_STL_CONSTRUCT_HPP

#include "iterator.hpp"
#include "type_traits.hpp"

namespace internals
{
  template<typename Tp>
    inline void _Destroy(Tp* pointer) { pointer->Tp(); }

  template<bool>
    struct destroy_aux
    {
      template<typename FowardIterator>
        static void destroy(FowardIterator first, FowardIterator last)
        {
          for (; first != last; ++first)
            _Destroy(&*first);
        };
    };

  template<>
    struct destroy_aux<true>
    {
      template<typename ForwardIterator>
        static void destroy(ForwardIterator, ForwardIterator)
        {};
    };

  template<typename ForwardIterator>
    inline void _Destroy(ForwardIterator first, ForwardIterator last)
    {
      typedef typename ft::iterator_traits<ForwardIterator>::value_type value;
      internals::destroy_aux<ft::is_scalar<value>::value>::destroy(first, last);
    }


}

#endif // !MY_STL_CONSTRUCT_HPP
