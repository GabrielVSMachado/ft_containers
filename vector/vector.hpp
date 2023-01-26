/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:14:48 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/01/25 22:07:36 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

// std implementation

//My implementation
#include "ReverseIterator.hpp"
#include "VectorBase.hpp"
#include "NormalIterator.hpp"
#include "iterator.hpp"
#include "my_stl_construct.hpp"
#include "type_traits.hpp"

namespace ft
{
  template<typename T>
    class vector : protected internals::VectorBase<T>
    {
      typedef internals::VectorBase<T> _Base;
      typedef ft::vector<T> vector_type;

    public:

      typedef T value_type;
      typedef size_t size_type;
      typedef std::ptrdiff_t difference_type;
      typedef typename _Base::allocator_type allocator_type;
      typedef typename allocator_type::pointer pointer;
      typedef typename allocator_type::const_pointer const_pointer;
      typedef typename allocator_type::reference reference;
      typedef typename allocator_type::const_reference const_reference;
      typedef internals::normal_iterator<pointer, vector_type> iterator;
      typedef internals::normal_iterator<const_pointer, vector_type> const_iterator;
      typedef ft::reverse_iterator<iterator> reverse_iterator;
      typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

      //Constructors
      explicit vector(allocator_type const & = allocator_type())
        : _Base(allocator_type()) {}

      //iterator methods
      iterator begin() { return iterator(this->Aimpl.start); }
      const_iterator begin() const
      {
        return const_iterator(this->Aimpl.start);
      }

      iterator end() { return iterator(this->Aimpl.finish); }
      const_iterator end() const { return const_iterator(this->Aimpl.finish); }

      reverse_iterator rbegin() { return reverse_iterator(end()); }
      const_reverse_iterator rbegin() const
      {
        return const_reverse_iterator(end());
      }

      reverse_iterator rend() { return reverse_iterator(begin()); }
      const_reverse_iterator rend() const { return reverse_iterator(begin()); }

      // capacity methods
      size_type capacity() const
      {
        return this->Aimpl.endOfStorage - this->Aimpl.start;
      }

      size_type size() const
      {
        return ft::distance(begin(), end());
      }

      bool empty() const { return size() == 0; }

      // modifiers methods
      void push_back(value_type const &value)
      {
        difference_type old_size, new_size;
        pointer hold_memory, current, tmp;

        old_size = size();

        if (!old_size)
        {
          this->Aimpl.start = this->allocate(2);
          this->Aimpl.finish = this->Aimpl.start;
          this->Aimpl.endOfStorage = this->Aimpl.start + 2;
        }
        else if (this->Aimpl.finish == this->Aimpl.endOfStorage)
        {
          hold_memory = this->Aimpl.start;
          new_size = old_size * 2;
          this->Aimpl.start = this->allocate(new_size);
          this->Aimpl.endOfStorage = this->Aimpl.start + new_size;
          for (current = this->Aimpl.start, tmp = hold_memory;
            tmp != this->Aimpl.finish;
            ++tmp, ++current)
          {
            *current = *tmp;
          }
          this->deallocate(hold_memory, old_size);
          this->Aimpl.finish = current;
        }
        *this->Aimpl.finish = value;
        ++this->Aimpl.finish;
      }
    };
}

#endif // !VECTOR_HPP
