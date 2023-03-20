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


#include <ctime>
#include <string>
#include <iostream>
#include "tests.h"

template <typename fn>
void print_time(std::string const &fnName, fn f)
{
  std::cout << "Executing: " << fnName << '\n';
  std::time_t const begging = time(0);
  f();
  double const diff = difftime(time(0), begging);
  std::cout << "Time of Execution in Seconds: " << diff << 's' << std::endl;
}

int main ()
{
  print_time("insert_1000000_integral_constant_at_begin", insert_1000000_integral_constant_at_begin);
  print_time("insert_1000000_integral_constant_at_end", insert_1000000000_integral_constant_at_end);
  return 0;
}
