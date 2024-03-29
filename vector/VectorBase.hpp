/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorBase.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:15:24 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/01/21 14:08:11 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORBASE_HPP
#define VECTORBASE_HPP

#include <cstddef>
#include <cstring>
#include <iostream>
#include <memory>

namespace internals
{

/**
 * This implementation is used to make easy handle allocation
 * and exceptions from the allocation's process
 **/
template<typename Tp, typename Alloc = std::allocator<Tp> >
  struct VectorBase
  {
    typedef Tp* Tp_pointer;
    typedef Alloc allocator_type;

    private:
      struct ImplementationAllocator : public Alloc
      {
        Tp_pointer start;
        Tp_pointer finish;
        Tp_pointer endOfStorage;

        ImplementationAllocator(
            allocator_type const &alloc = std::allocator<Tp>())
          : Alloc(alloc), start(0), finish(0), endOfStorage(0)
        {}
      };

    public:

    ImplementationAllocator Aimpl;

    allocator_type  get_allocator() const
    {
      return *static_cast<allocator_type const *>(&this->Aimpl);
    }

    VectorBase(allocator_type const &) : Aimpl() {}

    VectorBase(size_t n, allocator_type const &alloc = allocator_type())
      : Aimpl(alloc)
    {
      Aimpl.start = this->Aimpl.allocate(n);
      Aimpl.finish = Aimpl.start;
      Aimpl.endOfStorage = Aimpl.start + n;
      // std::memset(
      //   this->Aimpl.start, 0, (Aimpl.endOfStorage - Aimpl.start) * sizeof(Tp)
      // );
    }

    virtual ~VectorBase()
    {
      Aimpl.deallocate(Aimpl.start, Aimpl.endOfStorage - Aimpl.start);
    }

    Tp_pointer allocate(size_t n) { return Aimpl.allocate(n); }

    void deallocate(Tp_pointer p, size_t n)
    {
      if (p)
        Aimpl.deallocate(p, n);
    }

    void construct(Tp_pointer p, Tp const &value)
    {
      Aimpl.construct(p, value);
    }
  };
}

#endif // !VectorBase_HPP
