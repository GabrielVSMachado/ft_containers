/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:50:14 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/03/23 23:58:25 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>
#if STD == 1
  #include <utility>
  #include <map>
  namespace ft = std;
#else
  #include "map.hpp"
  #include "utility.hpp"
#endif


void insert_10000000_values()
{
  ft::map<int, int> __m;

  for (unsigned int i = 0; i < 10000000; ++i) {
    __m.insert(ft::make_pair(i, i));
  }
}

void insert_10000000_values_string()
{
  ft::map<int, std::string> __m;

  for (unsigned int i = 0; i < 10000000; ++i) {
    __m.insert(ft::make_pair(i, "42sp"));
  }
}

void insert_10000000_range()
{
  ft::map<unsigned int, unsigned int> __m;
  std::vector<ft::pair<unsigned int, unsigned int> > __v(10000000);

  std::vector<ft::pair<unsigned int, unsigned int> >::iterator it(__v.begin());
  for (unsigned int i = 0; it != __v.end(); ++it, ++i)
    *it = ft::make_pair(i, i);

  __m.insert(__v.begin(), __v.end());
}

void insert_10000000_range_string()
{
  ft::map<unsigned int, std::string> __m;
  std::vector<ft::pair<unsigned int, std::string> > __v(10000000);

  std::vector<ft::pair<unsigned int, std::string> >::iterator it(__v.begin());
  for (unsigned int i = 0; it != __v.end(); ++it, ++i)
    *it = ft::make_pair(i, "42sp");

  __m.insert(__v.begin(), __v.end());
}

void erase_1_element_at_position()
{
  ft::map<int, int> __m;

  for (unsigned int i = 0; i < 10000000; ++i)
    __m.insert(ft::make_pair(i, i));

  ft::map<int, int>::iterator it(__m.begin());
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  __m.erase(it);
}

void erase_key()
{
  ft::map<int, int> __m;

  for (unsigned int i = 0; i < 10000000; ++i)
    __m.insert(ft::make_pair(i, i));

  __m.erase(1000);
}

void erase_range()
{
  ft::map<int, int> __m;

  for (unsigned int i = 0; i < 10000000; ++i)
    __m.insert(ft::make_pair(i, i));

  ft::map<int, int>::iterator it(__m.begin());
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  __m.erase(it, __m.end());
}

void find_by_key()
{
  ft::map<int, int> __m;

  for (unsigned int i = 0; i < 10000000; ++i)
    __m.insert(ft::make_pair(i, i));

  __m.find(10000);
}

void equal_range_key()
{
  ft::map<int, int> __m;

  for (unsigned int i = 0; i < 10000000; ++i)
    __m.insert(ft::make_pair(i, i));

  __m.equal_range(10000);
}
