/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:21:23 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/03/19 23:21:25 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>
#if STD == 1
  #include <vector>
  namespace ft = std;
#else
  #include "vector.hpp"
#endif

void insert_1e5_integral_constant_at_begin()
{
  ft::vector<unsigned int> __v;

  for (unsigned int i = 0; i < 1e5; ++i)
    __v.insert(__v.begin(), i);
}

void insert_1e7_integral_constant_at_end()
{
  ft::vector<unsigned int> __v;

  for (unsigned int i = 0; i < 1e7; ++i)
    __v.insert(__v.end(), i);
}

void insert_1e6_integral_constant_at_position()
{
  ft::vector<unsigned int> __v(10);

  for (unsigned int i = 0; i < 1e6; ++i)
  {
    ft::vector<unsigned int>::iterator it = __v.begin() + 5;
    __v.insert(it, i);
  }
}

void insert_1e4__with_count_eq_10_integral_constant_at_begin()
{
  ft::vector<unsigned int> __v;

  for (unsigned int i = 0; i < 1e4; ++i)
    __v.insert(__v.begin(), 10, i);
}

void insert_1e5_with_count_eq_10_integral_constant_at_end()
{
  ft::vector<unsigned int> __v;

  for (unsigned int i = 0; i < 1e5; ++i)
    __v.insert(__v.end(), 10, i);
}

void insert_1e4_with_count_eq_10_integral_constant_at_position()
{
  ft::vector<unsigned int> __v(10);

  for (unsigned int i = 0; i < 1e4; ++i)
  {
    ft::vector<unsigned int>::iterator it = __v.begin() + 5;
    __v.insert(it, 10, i);
  }
}

void insert_1e4_at_begin()
{
  ft::vector<std::string> __v;

  for (unsigned int i = 0; i < 1e4; ++i)
    __v.insert(__v.begin(), "42sp");
}

void insert_1e7_at_end()
{
  ft::vector<std::string> __v;

  for (unsigned int i = 0; i < 1e7; ++i)
    __v.insert(__v.end(), "42sp");
}

void insert_1e4_at_position()
{
  ft::vector<std::string> __v(10);

  for (unsigned int i = 0; i < 1e4; ++i)
  {
    ft::vector<std::string>::iterator it = __v.begin() + 5;
    __v.insert(it, "42sp");
  }
}

void insert_1e4__with_count_eq_10_at_begin()
{
  ft::vector<std::string> __v;

  for (unsigned int i = 0; i < 1e4; ++i)
    __v.insert(__v.begin(), 10, "42sp");
}

void insert_1e6_with_count_eq_10_at_end()
{
  ft::vector<std::string> __v;

  for (unsigned int i = 0; i < 1e6; ++i)
    __v.insert(__v.end(), 10, "42sp");
}

void insert_1e4_with_count_eq_10_at_position()
{
  ft::vector<std::string> __v(10);

  for (unsigned int i = 0; i < 1e4; ++i)
  {
    ft::vector<std::string>::iterator it = __v.begin() + 5;
    __v.insert(it, 10, "42sp");
  }
}

void insert_1e8_integral_constant_with_range_II()
{
  ft::vector<int> __v(1e8, 42);

  __v.insert(__v.begin() + 5, __v.begin(), __v.end());
}


void insert_1e7_with_range_II()
{
  ft::vector<std::string> __v(1e7, "42");

  __v.insert(__v.begin() + 5, __v.begin(), __v.end());
}

void erase_1_element_in_the_middle_of_1e9_integral_constant()
{
  ft::vector<int> __v(1e9, 42);

  __v.erase(__v.begin() + 100);
}

void erase_1_element_in_the_middle_of_1e8()
{
  ft::vector<std::string> __v(1e8, "42");

  __v.erase(__v.begin() + 100);
}

void erase_range_element_in_the_middle_of_1e9_integral_constant()
{
  ft::vector<int> __v(1e9, 42);

  __v.erase(__v.begin() + 10, __v.begin() + 100);
}

void erase_range_element_in_the_middle_of_1e8()
{
  ft::vector<std::string> __v(1e8, "42");

  __v.erase(__v.begin() + 10, __v.begin() + 100);
}

void clear_1e8_integral_constant()
{
  ft::vector<int> __v(static_cast<int>(1e8), 42);

  __v.clear();
}

void clear_1e8()
{
  ft::vector<std::string> __v(1e8, "42");

  __v.clear();
}

void reserve_1e9_integral_constant()
{
  ft::vector<int> __v;

  __v.reserve(1e9);
}

void reserve_1e8()
{
  ft::vector<std::string> __v;

  __v.reserve(1e8);
}
