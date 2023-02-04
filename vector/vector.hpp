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
#include <iterator>
#include <memory>
#include <new>
#include <stdexcept>

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

    // Access methods
    reference at(size_type pos)
    {
      if (pos > size())
        throw std::out_of_range(
          "Parameter pos on 'at' method"
          " isn't a valid position"
        );

      return *(begin() + pos);
    }

    const_reference at(size_type pos) const
    {
      if (pos > size())
        throw std::out_of_range(
          "Parameter pos on 'at' method"
          " isn't a valid position"
        );

      return *(begin() + pos);
    }

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

    void reserve(size_type new_cap)
    {
      pointer newReservedMem;
      size_type _size;

      if (new_cap > max_size())
        throw std::length_error(
                "std::allocator<T>::allocate(size_t n) 'n' "
                "exceeds maximum supported size"
              );

      if (new_cap > capacity())
      {
        newReservedMem = this->allocate(new_cap);

        _size = size();

        this->fill_unintialiazed_copy<ft::is_integral<value_type>::value>(
          _size, this->Aimpl.start, newReservedMem
        );

        clearMemory();

        setMemoryAddress(
            newReservedMem,
            newReservedMem + _size,
            newReservedMem + new_cap
        );
      }
    }

    // modifiers methods
    void push_back(value_type const &value)
    {
      size_type _size, newCapacity;
      pointer newAllocatedMem;


      if (this->Aimpl.finish == this->Aimpl.endOfStorage)
      {
        _size = size();
        newCapacity = _size > 0 ? _size * 2 : 1;
        newAllocatedMem = this->allocate(newCapacity);

        this->fill_unintialiazed_copy<ft::is_integral<T>::value>(
          _size, this->Aimpl.start, newAllocatedMem
        );

        clearMemory();

        setMemoryAddress(
            newAllocatedMem,
            newAllocatedMem + _size,
            newAllocatedMem + newCapacity
        );
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
      iterator last(--end());

      if (pos == last)
      {
        pop_back();
        return end();
      }

      internalAssignmentCopy<ft::is_integral<value_type>::value>(
        pos + 1, end(), pos
      );
      internals::_Destroy(&*last);
      --this->Aimpl.finish;

      return pos;
    }

    iterator erase(iterator first, iterator last)
    {
      iterator _end;
      size_type newSize;

      _end = end();

      if (first == last)
        return last;


      if (last == _end)
      {
        internals::_Destroy(first, last);
        this->Aimpl.finish = &*first;
        return end();
      }

      newSize = size() - ft::distance(first, last);

      internalAssignmentCopy<ft::is_integral<value_type>::value>(
          last, _end, first
      );

      internals::_Destroy(last, _end);
      this->Aimpl.finish = this->Aimpl.start + newSize;

      return first;
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

    void swap(vector_type & other)
    {
      std::swap(this->Aimpl.start, other.Aimpl.start);
      std::swap(this->Aimpl.finish, other.Aimpl.finish);
      std::swap(this->Aimpl.endOfStorage, other.Aimpl.endOfStorage);
    }

  private:
    void clearMemory()
    {
      internals::_Destroy(begin(), end());
      this->deallocate(this->Aimpl.start, capacity());
    }

    void setMemoryAddress(
        pointer const &newAddress, pointer const &newFinish,
        pointer const &newEndOfStorage)
    {
      this->Aimpl.start = newAddress;
      this->Aimpl.finish = newFinish;
      this->Aimpl.endOfStorage = newEndOfStorage;
    }

    template<bool>
      void internalAssignmentCopy(iterator begin, iterator end, iterator dst)
      {
        std::copy(begin, end, dst);
      }

    template<>
      void internalAssignmentCopy<true>(
          iterator begin, iterator end, iterator dst)
      {
        std::memmove(
          &*dst, &*begin, ft::distance(begin, end) * sizeof(value_type)
        );
      }

    template<bool>
      void fill_unintialiazed_copy(
          size_type size, pointer src, pointer const& dst)
      {
        pointer current = dst;
        for (; size > 0 ; ++current, ++src, --size)
          this->construct(current, *src);
      }

    template<>
      void fill_unintialiazed_copy<true>(
          size_type size, pointer src, pointer const &dst)
      {
        std::memmove(dst, src, size * sizeof(value_type));
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
