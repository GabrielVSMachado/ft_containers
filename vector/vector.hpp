/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:14:48 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/01/21 14:08:10 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

// std implementation
#include <cstddef>
#include <exception>

//My implementation
#include "ReverseIterator.hpp"
#include "VectorBase.hpp"
#include "NormalIterator.hpp"
#include "my_stl_construct.hpp"

namespace ft
{
  template<typename T>
    class vector : protected internals::VectorBase<T>
    {
      typedef internals::VectorBase<T> _Base;
      typedef vector<T> vector_type;
      typedef std::allocator<T>  alloc;

    public:
      typedef T value_type;
      typedef size_t size_type;
      typedef std::ptrdiff_t difference_type;
      typedef typename alloc::pointer pointer;
      typedef typename _Base::allocator_type allocator_type;
      typedef typename alloc::const_pointer const_pointer;
      typedef typename alloc::reference reference;
      typedef typename alloc::const_reference const_reference;
      typedef internals::normal_iterator<pointer, vector_type> iterator;
      typedef internals::normal_iterator<const_pointer, vector_type> const_iterator;
      typedef ft::reverse_iterator<iterator> reverse_iterator;
      typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

      //Constructors
      explicit vector(allocator_type const &a = allocator_type()) : _Base(a) {}

      explicit vector(size_type count, value_type const &value = value_type(),
                      alloc const & = alloc()) : _Base(alloc())
      {
        allocator_type const tmp_allocator = this->get_allocator();
        pointer current;

        this->Aimpl.start = this->allocate(count);
        this->Aimpl.finish = this->Aimpl.start;
        this->Aimpl.endOfStorage = this->Aimpl.start + count;

        current = this->Aimpl.start;
        try
        {
          for (; count > -1; --count, ++current)
            tmp_allocator.construct(current, value);
        }
        catch (...)
        {
          internals::_Destroy(this->Aimpl.start, current);
          throw;
        }
        this->Aimpl.finish = current;
      }
    };
}

#endif // !VECTOR_HPP
