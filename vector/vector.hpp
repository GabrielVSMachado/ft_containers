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
#include <functional>
#include <memory>
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
        insert(end(), first, last);
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
      _uninitialized_fill_n(
        begin(),
        count,
        value,
        typename ft::is_integral<value_type>::type()
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
        _uninitialiazed_copy_backwards(
          first, last, begin() + length, ft::false_type()
        );
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

      if (new_cap > max_size())
        throw std::length_error(
                "std::allocator<T>::allocate(size_t n) 'n' "
                "exceeds maximum supported size"
              );

      if (new_cap > capacity())
        _copy_to_new_memory(new_cap, size());
    }

    // modifiers methods
    void push_back(value_type const &value)
    {
      size_type _size;
      pointer newAllocatedMem;


      if (this->Aimpl.finish == this->Aimpl.endOfStorage)
      {
        _size = size();
        _copy_to_new_memory(_size > 0 ? _size * 2 : 1, _size);
      }
      this->construct(this->Aimpl.finish, value);
      ++this->Aimpl.finish;
    }

    void pop_back() { (--this->Aimpl.finish)->~value_type(); }

    void clear()
    {
      internals::_Destroy(begin(), end());
      this->Aimpl.finish = this->Aimpl.start;
    }

    iterator erase(iterator pos)
    {
      if (pos != --end())
      {
        _uninitialiazed_copy(
          pos + 1, end(), pos, typename ft::is_integral<value_type>::type()
        );
      }
      pop_back();

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

      _uninitialiazed_copy(
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
      size_type const _size = size();

      if (_size > count)
        erase(begin() + count, end());
      else
        insert(end(), count - _size, value);
    }

    iterator insert(iterator pos, value_type const & value)
    {
      size_type const newSize = size() + 1;
      size_type const firstPartSize = pos - begin();

      if (newSize > capacity())
        _insert_in_new_memory_n_values(newSize, pos, 1, value);
      else
        _insert_n_values(pos, 1, value);

      return begin() + firstPartSize;
    }

    void insert(iterator pos, size_type count, value_type const &value)
    {
      size_type const newSize = size() + count;

      if (!count)
        return;

      if (newSize > capacity())
        _insert_in_new_memory_n_values(newSize, pos, count, value);
      else
        _insert_n_values(pos, count, value);
    }

    template<typename It>
    typename ft::enable_if<!is_integral<It>::value, void>::type
      insert(iterator pos, It first, It last)
      {
        size_type const newSize = size() + ft::distance(first, last);

        if (first == last)
          return;

        if (newSize > capacity())
          _insert_in_new_memory_n_values(newSize, pos, first, last);
        else
          _insert_n_values(pos, first, last);
      }

    void swap(vector_type & other)
    {
      std::swap(this->Aimpl.start, other.Aimpl.start);
      std::swap(this->Aimpl.finish, other.Aimpl.finish);
      std::swap(this->Aimpl.endOfStorage, other.Aimpl.endOfStorage);
    }

  private:
    typedef ft::is_integral<value_type> is_integral;

    void _insert_in_new_memory_n_values(
      size_type newSize,
      iterator pos,
      size_type count,
      value_type const &value)
    {
      size_type const newCapacity =
        newSize > 2 * capacity() ? newSize : 2 * capacity();
      size_type const firstPartSize = pos - begin();
      size_type const secondPartSize = end() - pos;
      pointer newMemory;

      newMemory = this->allocate(newCapacity);

      _uninitialiazed_copy_backwards(
        begin(),
        begin() + firstPartSize,
        iterator(newMemory + firstPartSize),
        typename is_integral::type()
      );
      _uninitialized_fill_n(
        iterator(newMemory + firstPartSize),
        count,
        value,
        typename is_integral::type()
      );
      _uninitialiazed_copy_backwards(
        pos,
        (pos + secondPartSize),
        iterator(newMemory + newSize),
        typename is_integral::type()
      );

      _clearMemory();
      _setMemoryAddress(
        newMemory,
        newMemory + newSize,
        newMemory + newCapacity
      );
    }

    template<typename Iter>
    typename ft::enable_if<!ft::is_integral<Iter>::value, void>::type
    _insert_in_new_memory_n_values(
      size_type const newSize, iterator pos, Iter first, Iter last)
    {
      pointer newMemory;
      size_type const firstPartSize = pos - begin();
      size_type const secondPartSize = end() - pos;
      size_type const newCapacity =
                        newSize > 2 * capacity() ? newSize: 2 * capacity();

      newMemory = this->allocate(newCapacity);

      _uninitialiazed_copy_backwards(
        begin(),
        begin() + firstPartSize,
        iterator(newMemory + firstPartSize),
        typename is_integral::type()
      );
      _uninitialiazed_copy_backwards(
        first,
        last,
        iterator(newMemory + (newSize - secondPartSize)),
        typename is_integral::type()
      );
      _uninitialiazed_copy_backwards(
        pos,
        pos + secondPartSize,
        iterator(newMemory + newSize),
        typename is_integral::type()
      );

      _clearMemory();
      _setMemoryAddress(
        newMemory,
        newMemory + newSize,
        newMemory + newCapacity
      );
    }

    void _insert_n_values(
        iterator pos, size_type count, value_type const &value)
    {
      size_type const firstPartSize = pos - begin();
      size_type const secondPartSize = end() - pos;
      size_type const newSize = firstPartSize + count + secondPartSize;

      _uninitialiazed_copy_backwards(
        pos,
        end(),
        begin() + newSize,
        typename is_integral::type()
      );
      _uninitialized_fill_n(
        pos,
        count,
        value,
        typename is_integral::type()
      );
      _setMemoryAddress(
        this->Aimpl.start,
        this->Aimpl.start + newSize,
        this->Aimpl.endOfStorage
      );
    }

    template<typename Iter>
    typename ft::enable_if<!ft::is_integral<Iter>::value, void>::type
    _insert_n_values(iterator pos, Iter first, Iter last)
    {
      size_type const length = ft::distance(first, last);
      size_type const newSize = size() + length;

      _uninitialiazed_copy_backwards(
        pos,
        end(),
        begin() + newSize,
        typename is_integral::type()
      );
      _uninitialiazed_copy_backwards(
        first,
        last,
        pos + length,
        typename is_integral::type()
      );
      _setMemoryAddress(
        this->Aimpl.start,
        this->Aimpl.start + newSize,
        this->Aimpl.endOfStorage
      );
    }

    void _copy_to_new_memory(
        size_type const &newCapacity, size_type const &_size)
    {
      pointer newAllocatedMem;

      newAllocatedMem = this->allocate(newCapacity);

      this->_uninitialiazed_copy_backwards(
        begin(),
        end(),
        iterator(newAllocatedMem + _size),
        typename is_integral::type()
      );

      _clearMemory();

      _setMemoryAddress(
          newAllocatedMem,
          newAllocatedMem + _size,
          newAllocatedMem + newCapacity
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
      void _uninitialiazed_copy(
          InputIt begin, InputIt end, InputItDst dst, ft::false_type)
      {
        std::uninitialized_copy(begin, end, dst);
      }

    template<typename Integral, typename InputItDst>
      void _uninitialiazed_copy(
          Integral begin, Integral end, InputItDst dst, ft::true_type)
      {
        std::uninitialized_copy(&*begin, &*end, &*dst);
      }

    void _uninitialized_fill_n(
        iterator begin, size_type count, value_type const &value, ft::true_type)
    {
      std::uninitialized_fill_n(&*begin, count, value);
    }

    void _uninitialized_fill_n(
      iterator begin, size_type count, value_type const &value, ft::false_type)
    {
      std::uninitialized_fill_n(begin, count, value);
    }

    template<typename Iter, typename IterDst>
    void _uninitialiazed_copy_backwards(
        Iter first, Iter last, IterDst dst, ft::true_type)
    {
      std::copy_backward(&*first, &*last, &*dst);
    }

    template<typename Iter, typename IterDst>
    void _uninitialiazed_copy_backwards(
        Iter first, Iter last, IterDst dst, ft::false_type)
    {
      while (first != last)
        this->construct(&*(--dst), *--last);
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
      return ft::lexicographical_compare(
          lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
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
