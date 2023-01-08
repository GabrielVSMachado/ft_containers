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

  // Define IsInteger
  template<typename T>
    struct IsInteger : public falseType {};

  template<>
    struct IsInteger<bool> : public trueType {};

  template<>
    struct IsInteger<char> : public trueType {};

  template<>
    struct IsInteger<signed char> : public trueType {};

  template<>
    struct IsInteger<unsigned char> : public trueType {};

  template<>
    struct IsInteger<wchar_t> : public trueType {};

  template<>
    struct IsInteger<short> : public trueType {};

  template<>
    struct IsInteger<unsigned short> : public trueType {};

  template<>
    struct IsInteger<int> : public trueType {};

  template<>
    struct IsInteger<unsigned int> : public trueType {};

  template<>
    struct IsInteger<long> : public trueType {};

  template<>
    struct IsInteger<unsigned long> : public trueType {};

  template<>
    struct IsInteger<float> : public falseType {};

  template<>
    struct IsInteger<double> : public falseType {};

  template<>
    struct IsInteger<long double> : public falseType {};

  // Define EnableIf
  template<bool, typename T = void>
    struct EnableIf {};

  template<typename T>
    struct EnableIf<true, T> : public TypeIdentity<T> {};
}

#endif // !TYPE_TRAITS
