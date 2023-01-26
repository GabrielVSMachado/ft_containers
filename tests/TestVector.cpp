#include <criterion/criterion.h>
#include "criterion/assert.h"
#include "criterion/criterion.h"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "vector.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include "algorithms.hpp"


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

Test(vector_size, expected_size_eq_0)
{
  ft::vector<int> my_vector;
  typename ft::vector<int>::size_type expected;

  expected = 0;
  cr_assert(my_vector.size() == expected);
}

Test(vector_size, expected_size_eq_20)
{
  ft::vector<int> my_vector;
  typename ft::vector<int>::size_type expected, result;

  for (int i = 0; i < 20; ++i)
    my_vector.push_back(42);

  expected = 20;
  result = my_vector.size();
  cr_assert(result == expected);
}

Test(vector_iterator, expected_all_values_from_iterator_eq_to_42)
{
  ft::vector<int> my_vector;
  std::vector<int> original_vector(20, 42);
  typename ft::vector<int>::iterator result;
  typename std::vector<int>::iterator expected = original_vector.begin();

  for (int i = 0; i < 20; ++i)
    my_vector.push_back(42);

  result = my_vector.begin();

  cr_assert(ft::equal(expected, original_vector.end(), result));
}

Test(vector_const_iterator, expected_all_values_from_const_iterator_eq_to_30)
{
  ft::vector<int> my_vector;
  std::vector<int> const original_vector(20, 42);
  typename ft::vector<int>::const_iterator result;
  typename std::vector<int>::const_iterator expected = original_vector.begin();

  for (int i = 0; i < 20; i++)
    my_vector.push_back(42);

  result = my_vector.begin();
  cr_assert(ft::equal(expected, original_vector.end(), result));
}

Test(vector_empty, expected_true)
{
  ft::vector<int> my_vector;

  cr_assert(my_vector.empty() == true);
}

Test(vector_empty, expected_false)
{
  ft::vector<int> my_vector;

  my_vector.push_back(42);

  cr_assert(my_vector.empty() == false);
}
