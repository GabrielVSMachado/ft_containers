/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:12:11 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/01/21 18:10:48 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS

#include <string>

namespace ft
{

  template<typename T, T v>
    struct integral_constant
    {
      typedef T valueType;
      typedef ft::integral_constant<T, v> type;
      static valueType const value = v;

      operator valueType() const { return value; }
    };

  typedef integral_constant<bool, true> true_type;
  typedef integral_constant<bool, false> false_type;

  template<typename T>
    struct TypeIdentity { typedef T valueType; };

  // Define Remove Modifiers
  template<typename T>
    struct remove_const : public TypeIdentity<T> {};

  template<typename T>
    struct remove_const< T const > : public TypeIdentity<T> {};

  template<typename T>
    struct remove_volatile : public TypeIdentity<T> {};

  template<typename T>
    struct remove_volatile<T volatile> : public TypeIdentity<T> {};

  template<typename T>
    struct remove_cv
      : public TypeIdentity<
                typename remove_volatile<
                          typename remove_const<T>::valueType
                        >::valueType
              > {};

  // Define IsSame
  template<typename T, typename U>
    struct is_same : public false_type {};

  template<typename T>
    struct is_same<T, T> : public true_type {};

  // Define IsIntegral
  template<typename T>
    struct is_integral_helper : public false_type {};

  template<>
    struct is_integral_helper<bool> : public true_type {};

  template<>
    struct is_integral_helper<char> : public true_type {};

  template<>
    struct is_integral_helper<signed char> : public true_type {};

  template<>
    struct is_integral_helper<unsigned char> : public true_type {};

  template<>
    struct is_integral_helper<wchar_t> : public true_type {};

  template<>
    struct is_integral_helper<char16_t> : public true_type {};

  template<>
    struct is_integral_helper<char32_t> : public true_type {};

  template<>
    struct is_integral_helper<short> : public true_type {};

  template<>
    struct is_integral_helper<unsigned short> : public true_type {};

  template<>
    struct is_integral_helper<int> : public true_type {};

  template<>
    struct is_integral_helper<unsigned int> : public true_type {};

  template<>
    struct is_integral_helper<long> : public true_type {};

  template<>
    struct is_integral_helper<unsigned long> : public true_type {};

  template<>
    struct is_integral_helper<long long> : public true_type {};

  template<>
    struct is_integral_helper<unsigned long long> : public true_type {};

  template<typename T>
    struct is_integral : public is_integral_helper<
                                typename remove_cv<T>::valueType
                              > {};

  // Define EnableIf
  template<bool, typename T = void>
    struct enable_if {};

  template<typename T>
    struct enable_if<true, T> : public TypeIdentity<T> {};
}

#endif // !TYPE_TRAITS
