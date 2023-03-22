/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:58:53 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/03/19 23:22:27 by gvitor-s         ###   ########.fr       */
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
  std::cout << "Time of Execution in Miliseconds: " << diff << "ms" << std::endl;
}

int main ()
{
  print_time("insert_100000_integral_constant_at_begin", insert_100000_integral_constant_at_begin);
  print_time("insert_10000000_integral_constant_at_end", insert_10000000_integral_constant_at_end);
  print_time("insert_1000000_integral_constant_at_position", insert_1000000_integral_constant_at_position);
  print_time("insert_10000__with_count_eq_10_integral_constant_at_begin", insert_10000__with_count_eq_10_integral_constant_at_begin);
  print_time("insert_100000_with_count_eq_10_integral_constant_at_end", insert_100000_with_count_eq_10_integral_constant_at_end);
  print_time("insert_10000_with_count_eq_10_integral_constant_at_position", insert_10000_with_count_eq_10_integral_constant_at_position);
  print_time("insert_10000_at_begin", insert_10000_at_begin);
  print_time("insert_10000000_at_end", insert_10000000_at_end);
  print_time("insert_10000_at_position", insert_10000_at_position);
  print_time("insert_10000__with_count_eq_10_at_begin", insert_10000__with_count_eq_10_at_begin);
  print_time("insert_1000000_with_count_eq_10_at_end", insert_1000000_with_count_eq_10_at_end);
  print_time("insert_10000_with_count_eq_10_at_position", insert_10000_with_count_eq_10_at_position);
  return 0;
}
