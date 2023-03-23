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
#if STD == 1
  #include <vector>
  namespace ft = std;
#else
  #include "vector.hpp"
#endif

void insert_100000_integral_constant_at_begin()
{
  ft::vector<unsigned int> __v;

  for (unsigned int i = 0; i < 100000; ++i)
    __v.insert(__v.begin(), i);
}

void insert_10000000_integral_constant_at_end()
{
  ft::vector<unsigned int> __v;

  for (unsigned int i = 0; i < 10000000; ++i)
    __v.insert(__v.end(), i);
}

void insert_1000000_integral_constant_at_position()
{
  ft::vector<unsigned int> __v(10);

  for (unsigned int i = 0; i < 1000000; ++i)
  {
    ft::vector<unsigned int>::iterator it = __v.begin() + 5;
    __v.insert(it, i);
  }
}

void insert_10000__with_count_eq_10_integral_constant_at_begin()
{
  ft::vector<unsigned int> __v;

  for (unsigned int i = 0; i < 10000; ++i)
    __v.insert(__v.begin(), 10, i);
}

void insert_100000_with_count_eq_10_integral_constant_at_end()
{
  ft::vector<unsigned int> __v;

  for (unsigned int i = 0; i < 100000; ++i)
    __v.insert(__v.end(), 10, i);
}

void insert_10000_with_count_eq_10_integral_constant_at_position()
{
  ft::vector<unsigned int> __v(10);

  for (unsigned int i = 0; i < 10000; ++i)
  {
    ft::vector<unsigned int>::iterator it = __v.begin() + 5;
    __v.insert(it, 10, i);
  }
}

void insert_10000_at_begin()
{
  ft::vector<std::string> __v;

  for (unsigned int i = 0; i < 10000; ++i)
    __v.insert(__v.begin(), "42sp");
}

void insert_10000000_at_end()
{
  ft::vector<std::string> __v;

  for (unsigned int i = 0; i < 10000000; ++i)
    __v.insert(__v.end(), "42sp");
}

void insert_10000_at_position()
{
  ft::vector<std::string> __v(10);

  for (unsigned int i = 0; i < 10000; ++i)
  {
    ft::vector<std::string>::iterator it = __v.begin() + 5;
    __v.insert(it, "42sp");
  }
}

void insert_10000__with_count_eq_10_at_begin()
{
  ft::vector<std::string> __v;

  for (unsigned int i = 0; i < 10000; ++i)
    __v.insert(__v.begin(), 10, "42sp");
}

void insert_1000000_with_count_eq_10_at_end()
{
  ft::vector<std::string> __v;

  for (unsigned int i = 0; i < 100000; ++i)
    __v.insert(__v.end(), 10, "42sp");
}

void insert_10000_with_count_eq_10_at_position()
{
  ft::vector<std::string> __v(10);

  for (unsigned int i = 0; i < 10000; ++i)
  {
    ft::vector<std::string>::iterator it = __v.begin() + 5;
    __v.insert(it, 10, "42sp");
  }
}

void insert_100000000_integral_constant_with_range_II()
{
  ft::vector<int> __v(100000000, 42);

  __v.insert(__v.begin() + 5, __v.begin(), __v.end());
}


void insert_10000000_with_range_II()
{
  ft::vector<std::string> __v(10000000, "42");

  __v.insert(__v.begin() + 5, __v.begin(), __v.end());
}

void erase_1_element_in_the_middle_of_1000000000_integral_constant()
{
  ft::vector<int> __v(1000000000, 42);

  __v.erase(__v.begin() + 100);
}

void erase_1_element_in_the_middle_of_100000000()
{
  ft::vector<std::string> __v(100000000, "42");

  __v.erase(__v.begin() + 100);
}

void erase_range_element_in_the_middle_of_1000000000_integral_constant()
{
  ft::vector<int> __v(1000000000, 42);

  __v.erase(__v.begin() + 10, __v.begin() + 100);
}

void erase_range_element_in_the_middle_of_100000000()
{
  ft::vector<std::string> __v(100000000, "42");

  __v.erase(__v.begin() + 10, __v.begin() + 100);
}

void clear_100000000_integral_constant()
{
  ft::vector<int> __v(1000000000, 42);

  __v.clear();
}

void clear_10000000()
{
  ft::vector<std::string> __v(100000000, "42");

  __v.clear();
}

void reserve_1000000000_integral_constant()
{
  ft::vector<int> __v;

  __v.reserve(1000000000);
}

void reserve_100000000()
{
  ft::vector<std::string> __v;

  __v.reserve(100000000);
}
