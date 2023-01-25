#include <criterion/criterion.h>
#include "criterion/criterion.h"
#include "vector.hpp"
#include <iostream>


Test(vector_capacity, expected_capacity_eq_2)
{
  ft::vector<int> my_vector;
  typename ft::vector<int>::size_type expected, result;

  my_vector.push_back(1);
  my_vector.push_back(2);

  expected = 2;
  result = my_vector.capacity();
  cr_assert(expected == result);
}

Test(vector_capacity, expected_capacity_eq_4)
{
  ft::vector<int> my_vector;
  typename ft::vector<int>::size_type expected, result;

  my_vector.push_back(1);
  my_vector.push_back(2);
  my_vector.push_back(3);
  my_vector.push_back(4);

  expected = 4;
  result = my_vector.capacity();
  cr_assert(result == expected);
}
