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
#include <algorithm>
#include <cstdio>
#include <iostream>

//My implementation
#include "ReverseIterator.hpp"
#include "VectorBase.hpp"
#include "NormalIterator.hpp"
#include "iterator.hpp"
#include "my_stl_construct.hpp"
#include "type_traits.hpp"
#include <cstring>
#include <memory>

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
      const_reverse_iterator rend() const
      {
        return const_reverse_iterator(begin());
      }

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

      size_type max_size() const
      {
        return this->get_allocator().max_size();
      }

      // modifiers methods
      void push_back(value_type const &value)
      {
        size_type _size, newSize;
        pointer src, oldFinish;


        if (this->Aimpl.finish == this->Aimpl.endOfStorage)
        {
          _size = size();
          newSize = _size > 0 ? _size * 2 : 1;
          src = this->Aimpl.start;
          oldFinish = this->Aimpl.finish;
          this->Aimpl.start = this->allocate(newSize);
          this->Aimpl.endOfStorage = this->Aimpl.start + newSize;
          this->fill_unintialiazed_copy<
                                        ft::is_integral<T>::value
                                      >(_size, src, this->Aimpl.start);
          internals::_Destroy(iterator(src), iterator(oldFinish));
          this->deallocate(src, _size);
        }
        this->construct(this->Aimpl.finish, value);
        ++this->Aimpl.finish;
      }

      void pop_back() { (this->Aimpl.finish--)->~value_type(); }

      void clear()
      {
        internals::_Destroy(begin(), end());
        this->Aimpl.finish = this->Aimpl.start;
      }

      iterator erase(iterator pos)
      {
        iterator last, followingIterator;

        last = --end();

        if (pos == last)
        {
          pop_back();
          followingIterator = end();
        }
        else
        {
          internals::_Destroy(&*pos);
          followingIterator = pos++;
          fill_unintialiazed_copy<ft::is_integral<value_type>::value>(
              last - followingIterator, &*pos, &*followingIterator
          );
        }
        return followingIterator;
      }

      iterator erase(iterator first, iterator last)
      {
        iterator _end, followingIterator;

        _end = end();

        if (first == last)
          return last;

        internals::_Destroy(first, last);

        if (last == _end)
        {
          this->Aimpl.finish = &*first;
          followingIterator = end();
        }

        else
        {
          followingIterator = first;
          fill_unintialiazed_copy<ft::is_integral<value_type>::value>(
              _end - last, &*last, &*first
          );
        }

        return followingIterator;
      }

      void resize(size_type count, value_type value = value_type())
      {
        size_type _size;

        _size = size();

        if (_size > count)
          erase(begin() + count, end());
        else
        {
          for (; _size != count; --count)
            push_back(value);
        }
      }

      iterator insert(iterator pos, value_type const & value)
      {
        size_type _size, lengthToCopy;
        iterator insertedValuePos;

        if (pos == end())
        {
          push_back(value);
          insertedValuePos = --end();
        }
        else
        {
          _size = size();
          lengthToCopy = ft::distance(pos, end());
          insert(pos, 1, value);
          insertedValuePos = begin() + (_size - lengthToCopy);
        }

        return insertedValuePos;
      }

      void insert(iterator pos, size_type count, value_type const &value)
      {
        internInsert(pos, count, value, ft::true_type());
      }

      template<typename InputIt>
        void insert(iterator pos, InputIt first, InputIt last)
        {
          internInsert(
              pos, first, last, typename ft::is_integral<InputIt>::type()
          );
        }


    private:
      template<bool>
        void fill_unintialiazed_copy(
            size_type size, pointer src, pointer const& dst)
        {
          pointer current = dst;
          for (; size > 0 ; ++current, ++src, --size)
            this->construct(current, *src);
          this->Aimpl.finish = &*current;
        }

      template<>
        void fill_unintialiazed_copy<true>(
            size_type size, pointer src, pointer const &dst)
        {
          std::memmove(dst, src, size * sizeof(value_type));
          this->Aimpl.finish = dst + size;
        }

      template<typename InputIt>
        void internInsert(
            iterator pos, InputIt first, InputIt last, ft::false_type)
        {
          size_type _size, lengthToCopy, lengthToAdd;
          iterator insertedValuePos, endToCopy, startToCopy, destination;

          if (first == last)
            return;

          lengthToAdd = ft::distance(first, last);
          _size = size();
          lengthToCopy = ft::distance(pos, end());

          if (_size + lengthToAdd > capacity())
            resize(_size + lengthToAdd);

          endToCopy = begin() + (_size - lengthToCopy);
          startToCopy = begin() + _size;
          destination = end();

          insertedValuePos = std::copy_backward(
                              endToCopy, startToCopy, destination
                            );
          --insertedValuePos;
          for (; first != last; ++first, --insertedValuePos)
            *insertedValuePos = *first;
        }

      template<typename Integral>
        void internInsert(
            iterator pos, size_type count, Integral const& value,ft::true_type)
        {
          size_type _size, lengthToCopy;
          iterator insertedValuePos, endToCopy, startToCopy, destination;

          _size = size();

          if (pos == end())
            resize(_size + count, value);

          else
          {
            lengthToCopy = ft::distance(pos, end());

            if (_size + count > capacity())
              resize(_size + count);

            endToCopy = begin() + (_size - lengthToCopy);
            startToCopy = begin() + _size;
            destination = end();

            insertedValuePos = std::copy_backward(
                                endToCopy, startToCopy, destination
                              );
            --insertedValuePos;
            for (; count > 0; --count, --insertedValuePos)
              *insertedValuePos = value;
          }
        }
    };
}

#endif // !VECTOR_HPP
