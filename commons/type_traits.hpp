/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:12:11 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/01/25 17:17:11 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <string>

namespace ft
{

  template<typename T, T v>
    struct integral_constant
    {
      typedef T value_type;
      typedef ft::integral_constant<T, v> type;
      static value_type const value = v;

      operator value_type() const { return value; }
    };

  typedef integral_constant<bool, true> true_type;
  typedef integral_constant<bool, false> false_type;

  template<typename T>
    struct TypeIdentity { typedef T value_type; };

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
                          typename remove_const<T>::value_type
                        >::value_type
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
                                typename remove_cv<T>::value_type
                              > {};

  // Define enable_if
  template<bool, typename T = void>
    struct enable_if {};

  template<typename T>
    struct enable_if<true, T> : public TypeIdentity<T> {};

  // Define is_floating_point
  template<typename T>
    struct is_floating_point
      : public
      ft::integral_constant<
        bool,
        ft::is_same<float, typename ft::remove_cv<T>::value_type>::value ||
        ft::is_same<double, typename ft::remove_cv<T>::value_type>::value ||
        ft::is_same<long double, typename ft::remove_cv<T>::value_type>::value
      > {};

  //Define is_arithmetic
  template<typename T>
    struct is_arithmetic
    : public
      integral_constant<
        bool,
        ft::is_integral<T>::value || ft::is_floating_point<T>::value
      >
    {};

  // Define is_pointer
  template<typename T>
    struct is_pointer : public false_type {};

  template<typename T>
    struct is_pointer<T*> : public true_type {};

  template<typename T>
    struct is_pointer<T* const> : public true_type {};

  template<typename T>
    struct is_pointer<T* volatile> : public true_type {};

  template<typename T>
    struct is_pointer<T* const volatile> : public true_type {};

  // Define is_member_pointer
  template<typename T>
    struct is_member_pointer_helper : public false_type {};

  template<typename T, typename U>
    struct is_member_pointer_helper<T U::*> : public true_type {};

  template<typename T>
    struct is_member_pointer
    : public ft::is_member_pointer_helper<typename ft::remove_cv<T>::value_type>
    {};

  // Define is_enum
  template<typename T>
    struct is_enum : public integral_constant<bool, __is_enum(T)> {};

  // Define is_scalar
  template<typename T>
    struct is_scalar
    : public integral_constant<
          bool,
          ft::is_arithmetic<T>::value     ||
          ft::is_pointer<T>::value        ||
          ft::is_member_pointer<T>::value ||
          ft::is_enum<T>::value> {};
}

#endif // !TYPE_TRAITS
