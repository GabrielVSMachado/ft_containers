/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 14:06:05 by gvitor-s          #+#    #+#             */
/*   Updated: 2023/01/21 14:08:03 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type_traits.hpp"
#include <iostream>
#include "vector.hpp"

int main (void)
{
  std::cout << ft::is_integral<unsigned long long>::value << '\n';
  return 0;
}
