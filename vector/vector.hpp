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
#include <cstring>
#include <iostream>
#include <stdexcept>

//My implementation
#include "ReverseIterator.hpp"
#include "VectorBase.hpp"
#include "NormalIterator.hpp"
#include "iterator.hpp"
#include "my_stl_construct.hpp"
#include "type_traits.hpp"
#include "algorithms.hpp"
#include "utility.hpp"

namespace ft
{
template<typename T, typename Alloc = std::allocator<T> >
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
    explicit vector(allocator_type const &alloc = allocator_type())
      : _Base(alloc) {}

    vector(vector_type const &other) : _Base(other.get_allocator())
    {
      *this = other;
    }

    explicit vector(size_type n, value_type const &value = value_type(),
        allocator_type const &alloc = allocator_type())
      : _Base(n, alloc)
    {
      insert(end(), n, value);
    }

    template<typename Iter>
      vector(Iter first,
        typename ft::enable_if<!ft::is_integral<Iter>::value, Iter>::type last,
        allocator_type const &alloc = allocator_type())
        : _Base(ft::distance(first, last), alloc)
      {
        insert(begin(), first, last);
      }

    ~vector()  { internals::_Destroy(begin(), end()); }

    allocator_type get_allocator() const { return _Base::get_allocator(); }

    vector_type& operator=(vector_type const &other)
    {
      assign(other.begin(), other.end());
      return *this;
    }

    void assign(size_type count, value_type const &value)
    {
      reserve(count);
      if (count < size())
        internals::_Destroy(begin()+count, end());
      _setMemoryAddress(
        this->Aimpl.start,
        this->Aimpl.start + count,
        this->Aimpl.endOfStorage
      );
      _assignmentValue(
        begin(), end(), value, typename ft::is_integral<value_type>::type()
      );
    }

    template<typename It>
      void assign(
        It first,
        typename ft::enable_if<!ft::is_integral<It>::value, It>::type last)
      {
        size_type length = ft::distance(first, last);
        reserve(length);
        if (length < size())
          internals::_Destroy(begin()+length, end());
        _setMemoryAddress(
          this->Aimpl.start,
          this->Aimpl.start + length,
          this->Aimpl.endOfStorage
        );
        _assignmentCopy(first, last, begin(), ft::false_type());
      }

    // Access methods
    reference at(size_type pos)
    {
      if (pos > size())
        throw std::out_of_range(
          "Parameter pos on 'at' method"
          " isn't a valid position"
        );

      return (operator[](pos));
    }

    const_reference at(size_type pos) const
    {
      if (pos > size())
        throw std::out_of_range(
          "Parameter pos on 'at' method"
          " isn't a valid position"
        );

      return (operator[](pos));
    }

    reference front() { return *begin(); }
    const_reference front() const { return *begin(); }

    reference back() { return *--end(); }
    const_reference back() const { return *--end(); }

    reference operator[](size_type pos) { return *(begin() + pos); }
    const_reference operator[](size_type pos) const { return *(begin() + pos); }

    pointer data() { return this->Aimpl.start; }
    const_pointer data() const { return this->Aimpl.start; }

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

        this->fill_unintialiazed_copy(
          _size,
          this->Aimpl.start,
          newReservedMem,
          typename is_integral::type()
        );

        _clearMemory();

        _setMemoryAddress(
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

        this->fill_unintialiazed_copy(
          _size,
          this->Aimpl.start,
          newAllocatedMem,
          typename is_integral::type()
        );

        _clearMemory();

        _setMemoryAddress(
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

      _assignmentCopy(
        pos + 1, end(), pos, typename ft::is_integral<value_type>::type()
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

      _assignmentCopy(
          last, _end, first, typename ft::is_integral<value_type>::type()
      );

      internals::_Destroy(last, _end);
      _setMemoryAddress(
          this->Aimpl.start,
          this->Aimpl.start + newSize,
          this->Aimpl.endOfStorage
      );

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
      pointer newMemory;
      size_type const newSize = size() + 1;
      size_type const firstPartSize = pos - begin();
      size_type const secondPartSize = end() - pos;

      if (newSize > capacity())
      {
        newMemory = this->allocate(newSize);

        fill_unintialiazed_copy(
          firstPartSize,
          &*begin(),
          newMemory,
          typename is_integral::type()
        );
        this->construct(newMemory + firstPartSize, value);
        fill_unintialiazed_copy(
          secondPartSize,
          &*pos,
          newMemory + firstPartSize + 1,
          typename is_integral::type()
        );

        _clearMemory();
        _setMemoryAddress(
          newMemory,
          newMemory + newSize,
          newMemory + newSize
        );
      }
      else
      {
        fill_unintialiazed_copy(
          secondPartSize,
          &*pos,
          &*(pos + 1),
          typename is_integral::type()
        );
        ++this->Aimpl.finish;
        this->construct(&*pos, value);
      }
      return begin() + firstPartSize;
    }

    // void insert(iterator pos, size_type count, value_type const &value)
    // {
    // }
    //
    // template<typename It>
    //   typename ft::enable_if<!ft::is_integral<It>::value, void>::type
    //   insert(iterator pos, It first, It last)
    //   {
    //   }

    void swap(vector_type & other)
    {
      std::swap(this->Aimpl.start, other.Aimpl.start);
      std::swap(this->Aimpl.finish, other.Aimpl.finish);
      std::swap(this->Aimpl.endOfStorage, other.Aimpl.endOfStorage);
    }

  private:
    typedef ft::is_integral<value_type> is_integral;

    iterator _copyAfterRange(size_type size, size_type lengthToCopy)
    {
      return std::copy_backward(
              begin() + (size - lengthToCopy), begin() + size, end()
            );
    }

    void _clearMemory()
    {
      clear();
      this->deallocate(this->Aimpl.start, capacity());
    }

    void _setMemoryAddress(
        pointer const &newAddress, pointer const &newFinish,
        pointer const &newEndOfStorage)
    {
      this->Aimpl.start = newAddress;
      this->Aimpl.finish = newFinish;
      this->Aimpl.endOfStorage = newEndOfStorage;
    }

    template<typename InputIt, typename InputItDst>
      void _assignmentCopy(
          InputIt begin, InputIt end, InputItDst dst, ft::false_type)
      {
        std::copy(begin, end, dst);
      }

    template<typename Integral, typename InputItDst>
      void _assignmentCopy(
          Integral begin, Integral end, InputItDst dst, ft::true_type)
      {
        std::memmove(
          &*dst, &*begin, ft::distance(begin, end) * sizeof(value_type)
        );
      }

    void _assignmentValue(
        iterator begin, iterator end, value_type const &value, ft::true_type)
    {
      std::memset(&*begin, value, ft::distance(begin, end));
    }


    void _assignmentValue(
        iterator begin, iterator end, value_type const &value, ft::false_type)
    {
      while (begin != end)
      {
        this->construct(&*begin, value);
        ++begin;
      }
    }

      void fill_unintialiazed_copy(
          size_type size, pointer src, pointer dst, ft::true_type)
      {
        std::memmove(dst, src, size * sizeof(value_type));
      }

      void fill_unintialiazed_copy(
          size_type size, pointer src, pointer dst, ft::false_type)
      {
        if (dst > src)
        {
          for (; size > 0 ; --size)
            this->construct(dst + size, *(src + size));
        }
        else
        {
          for (; size > 0 ; ++dst, ++src, --size)
            this->construct(dst, *src);
        }
      }

  };

  // Non member functions booleans operators vector
  template<typename T, typename Alloc>
    bool operator==(
        ft::vector<T, Alloc> const &lhs, ft::vector<T, Alloc> const &rhs)
    {
      return (
        lhs.size() == rhs.size()
        &&
        ft::equal(lhs.begin(), lhs.end(), rhs.begin())
      );
    }

  template<typename T, typename Alloc>
    bool operator<(
        ft::vector<T, Alloc> const &lhs, ft::vector<T, Alloc> const &rhs)
    {
      typedef typename ft::vector<T, Alloc>::const_iterator const_iterator;

      return ft::equal<
              const_iterator, const_iterator, bool (*)(T const &, T const &)
              >(lhs.begin(), lhs.end(), rhs.begin(), ft::cmp_less);
    }

  template<typename T, typename Alloc>
    bool operator!=(
        ft::vector<T, Alloc> const &lhs, ft::vector<T, Alloc> const &rhs)
    {
      return !(lhs == rhs);
    }

  template<typename T, typename Alloc>
    bool operator>(
        ft::vector<T, Alloc> const &lhs, ft::vector<T, Alloc> const &rhs)
    {
      return rhs < lhs;
    }

  template<typename T, typename Alloc>
    bool operator>=(
        ft::vector<T, Alloc> const &lhs, ft::vector<T, Alloc> const &rhs)
    {
      return !(lhs < rhs);
    }

  template<typename T, typename Alloc>
    bool operator<=(
        ft::vector<T, Alloc> const &lhs, ft::vector<T, Alloc> const &rhs)
    {
      return !(rhs < lhs);
    }
}

#endif // !VECTOR_HPP
