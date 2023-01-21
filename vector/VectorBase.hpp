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
#include <memory>

namespace internals
{

/**
 * This implementation is used to make easy handle allocation
 * and exceptions from the allocation's process
 **/
template<typename Tp>
  struct VectorBase
  {
    typedef Tp* Tp_pointer;
    typedef std::allocator<Tp> allocator_type;

    private:
      struct ImplementationAllocator : public std::allocator<Tp>
      {
        Tp_pointer start;
        Tp_pointer finish;
        Tp_pointer end_of_storage;

        ImplementationAllocator() : start(0), finish(0), end_of_storage(0) {}
      };

    public:

    ImplementationAllocator Aimpl;

    allocator_type  get_allocator() const
    {
      return *static_cast<allocator_type const *>(&this->Aimpl);
    }

    VectorBase() : Aimpl() {}

    VectorBase(size_t n) : Aimpl()
    {
      Aimpl.start = this->Aimpl.allocate(n);
      Aimpl.finish = Aimpl.start;
      Aimpl.end_of_storage = Aimpl.start + n;
    }

    ~VectorBase()
    {
      Aimpl.deallocate(Aimpl.start, Aimpl.end_of_storage - Aimpl.start);
    }

    Tp_pointer allocate(size_t n) { return Aimpl.allocate(n); }

    void deallocate(Tp_pointer p, size_t n)
    {
      if (p)
        Aimpl.deallocate(p, n);
    }
  };
}

#endif // !VectorBase_HPP
