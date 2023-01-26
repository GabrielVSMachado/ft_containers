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

Test(vector_max_size, expected_size_max_of_char)
{
  ft::vector<char> my_vector;
  std::vector<char> original;

  cr_assert(my_vector.max_size() == original.max_size());
}


Test(vector_max_size, expected_size_max_of_int)
{
  ft::vector<int> my_vector;
  std::vector<int> original;

  cr_assert(my_vector.max_size() == original.max_size());
}

Test(vector_max_size, expected_size_max_of_float)
{
  ft::vector<float> my_vector;
  std::vector<float> original;

  cr_assert(my_vector.max_size() == original.max_size());
}


Test(vector_max_size, expected_size_max_of_double)
{
  ft::vector<double> my_vector;
  std::vector<double> original;

  cr_assert(my_vector.max_size() == original.max_size());
}

Test(vector_max_size, expected_size_max_of_long_long_int)
{
  ft::vector<long long int> my_vector;
  std::vector<long long int> original;

  cr_assert(my_vector.max_size() == original.max_size());
}

Test(vector_max_size, expected_size_max_of_std_string)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original;

  cr_assert(my_vector.max_size() == original.max_size());
}
