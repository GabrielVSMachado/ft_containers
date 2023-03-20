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

#include "vector.hpp"

void insert_1000000_integral_constant_at_begin()
{
  ft::vector<unsigned int> __v;

  for (unsigned int i = 0; i < 1000000; ++i)
    __v.insert(__v.begin(), i);
}

void insert_1000000000_integral_constant_at_end()
{
  ft::vector<unsigned int> __v;

  for (unsigned int i = 0; i < 1000000000; ++i)
    __v.insert(__v.end(), i);
}

// void insert_