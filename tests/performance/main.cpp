/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:58:53 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/03/24 00:07:19 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <time.h>
#include <string>
#include <iostream>
#include "tests.h"

template <typename fn>
void print_time(std::string const &fnName, fn f)
{
  clock_t begging, end;
  std::cout << "Executing: " << fnName << '\n';
  begging = clock();
  f();
  end = clock();
  double const diff = static_cast<double>(end - begging) / CLOCKS_PER_SEC;
  std::cout << "Time_of_Execution_in_Miliseconds: " << diff << "ms" << std::endl;
}

int main ()
{
  {
    std::cout << "Vector_tests " << std::endl;
    print_time("insert_1e5_integral_constant_at_begin", insert_1e5_integral_constant_at_begin);
    print_time("insert_1e7_integral_constant_at_end", insert_1e7_integral_constant_at_end);
    print_time("insert_1e6_integral_constant_at_position", insert_1e6_integral_constant_at_position);
    print_time("insert_1e4__with_count_eq_10_integral_constant_at_begin", insert_1e4__with_count_eq_10_integral_constant_at_begin);
    print_time("insert_1e5_with_count_eq_10_integral_constant_at_end", insert_1e5_with_count_eq_10_integral_constant_at_end);
    print_time("insert_1e4_with_count_eq_10_integral_constant_at_position", insert_1e4_with_count_eq_10_integral_constant_at_position);
    print_time("insert_1e4_at_begin", insert_1e4_at_begin);
    print_time("insert_1e7_at_end", insert_1e7_at_end);
    print_time("insert_1e4_at_position", insert_1e4_at_position);
    print_time("insert_1e4__with_count_eq_10_at_begin", insert_1e4__with_count_eq_10_at_begin);
    print_time("insert_1e6_with_count_eq_10_at_end", insert_1e6_with_count_eq_10_at_end);
    print_time("insert_1e4_with_count_eq_10_at_position", insert_1e4_with_count_eq_10_at_position);
    print_time("insert_1e8_integral_constant_with_range_II", insert_1e8_integral_constant_with_range_II);
    print_time("insert_1e7_with_range_II", insert_1e7_with_range_II);
    print_time("erase_1_element_in_the_middle_of_1e9_integral_constant", erase_1_element_in_the_middle_of_1e9_integral_constant);
    print_time("erase_1_element_in_the_middle_of_1e8", erase_1_element_in_the_middle_of_1e8);
    print_time("erase_range_element_in_the_middle_of_1e9_integral_constant", erase_range_element_in_the_middle_of_1e9_integral_constant);
    print_time("erase_range_element_in_the_middle_of_1e8", erase_range_element_in_the_middle_of_1e8);
    print_time("clear_1e8_integral_constant", clear_1e8_integral_constant);
    print_time("clear_1e8", clear_1e8);
    print_time("reserve_1e9_integral_constant", reserve_1e9_integral_constant);
    print_time("reserve_1e8", reserve_1e8);
    std::cout << std::endl;
  }
  {
    std::cout << "Map_Test " << std::endl;
    print_time("insert_1e7_values", insert_1e7_values);
    print_time("insert_1e7_values_string", insert_1e7_values_string);
    print_time("insert_1e7_range", insert_1e7_range);
    print_time("insert_1e7_range_string", insert_1e7_range_string);
    print_time("erase_1_element_at_position", erase_1_element_at_position);
    print_time("erase_key", erase_key);
    print_time("erase_range", erase_range);
    print_time("find_by_key", find_by_key);
    print_time("equal_range_key", equal_range_key);
  }
  return 0;
}
