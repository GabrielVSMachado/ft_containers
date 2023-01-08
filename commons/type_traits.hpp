/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:12:11 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/01/08 16:41:16 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS

#include <string>

namespace ft
{

  template<typename T, T v>
    struct IntegralConstant
    {
      typedef T valueType;
      typedef ft::IntegralConstant<T, v> type;
      static valueType const value = v;

      operator valueType() const { return value; }
    };

  typedef IntegralConstant<bool, true> trueType;
  typedef IntegralConstant<bool, false> falseType;

  template<typename T>
    struct TypeIdentity { typedef T valueType; };

  // Define Remove Modifiers
  template<typename T>
    struct RemoveConst : public TypeIdentity<T> {};

  template<typename T>
    struct RemoveConst< T const > : public TypeIdentity<T> {};

  template<typename T>
    struct RemoveVolatile : public TypeIdentity<T> {};

  template<typename T>
    struct RemoveVolatile<T volatile> : public TypeIdentity<T> {};

  template<typename T>
    struct RemoveConstAndVolatile
      : public TypeIdentity<
                typename RemoveVolatile<
                          typename RemoveConst<T>::valueType
                        >::valueType
              > {};

  // Define IsSame
  template<typename T, typename U>
    struct IsSame : public falseType {};

  template<typename T>
    struct IsSame<T, T> : public trueType {};

  // Define IsIntegral
  template<typename T>
    struct IsIntegralHelper : public falseType {};

  template<>
    struct IsIntegralHelper<bool> : public trueType {};

  template<>
    struct IsIntegralHelper<char> : public trueType {};

  template<>
    struct IsIntegralHelper<signed char> : public trueType {};

  template<>
    struct IsIntegralHelper<unsigned char> : public trueType {};

  template<>
    struct IsIntegralHelper<wchar_t> : public trueType {};

  template<>
    struct IsIntegralHelper<char16_t> : public trueType {};

  template<>
    struct IsIntegralHelper<char32_t> : public trueType {};

  template<>
    struct IsIntegralHelper<short> : public trueType {};

  template<>
    struct IsIntegralHelper<unsigned short> : public trueType {};

  template<>
    struct IsIntegralHelper<int> : public trueType {};

  template<>
    struct IsIntegralHelper<unsigned int> : public trueType {};

  template<>
    struct IsIntegralHelper<long> : public trueType {};

  template<>
    struct IsIntegralHelper<unsigned long> : public trueType {};

  template<>
    struct IsIntegralHelper<long long> : public trueType {};

  template<>
    struct IsIntegralHelper<unsigned long long> : public trueType {};

  template<typename T>
    struct IsIntegral : public IsIntegralHelper<
                                typename RemoveConstAndVolatile<T>::valueType
                              > {};

  // Define EnableIf
  template<bool, typename T = void>
    struct EnableIf {};

  template<typename T>
    struct EnableIf<true, T> : public TypeIdentity<T> {};
}

#endif // !TYPE_TRAITS
