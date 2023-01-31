#include <criterion/criterion.h>
#include "criterion/assert.h"
#include "criterion/criterion.h"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "vector.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
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
  typename std::vector<int>::const_iterator expected = original_vector.begin();

  for (int i = 0; i < 20; i++)
    my_vector.push_back(42);

  cr_assert(ft::equal(expected, original_vector.end(), my_vector.begin()));
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

Test(vector_push_back, expected_right_sequence_values_for_no_integral_types)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original(3, "42sp");
  typename ft::vector<std::string>::iterator result;

  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");

  cr_assert(ft::equal(original.begin(), original.end(), my_vector.begin()));
}

Test(vector_pop_back, expected_vectors_with_the_same_number_of_size)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original(2, "42sp");

  my_vector.push_back("42sp");
  my_vector.push_back("42sp");

  original.pop_back();
  my_vector.pop_back();

  cr_assert(original.size() == my_vector.size());
}

Test(vector_pop_back, expected_vectors_with_same_capacity)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original(2, "42sp");

  my_vector.push_back("42sp");
  my_vector.push_back("42sp");

  original.pop_back();
  my_vector.pop_back();

  cr_assert(original.capacity() == my_vector.capacity());
}

Test(vector_pop_back, expected_same_values_for_vectors_using_iterator)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original(4, "42sp");

  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");

  original.pop_back();
  my_vector.pop_back();

  cr_assert(ft::equal(original.begin(), original.end(), my_vector.begin()));
}

Test(vector_pop_back, expected_same_values_for_vectors_using_reverse_iterator)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original(4, "42sp");

  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");

  original.pop_back();
  my_vector.pop_back();

  cr_assert(ft::equal(original.rbegin(), original.rend(), my_vector.rbegin()));
}

Test(vector_clear, expected_the_same_value_of_capacity)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original(4, "42sp");

  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");

  my_vector.clear();
  original.clear();
  cr_assert(my_vector.capacity() == original.capacity());
}

Test(vector_clear, expected_size_eq_0)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original(4, "42sp");

  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");

  my_vector.clear();
  original.clear();
  cr_assert(my_vector.size() == original.size());
}

Test(vector_clear, expected_same_values_for_vectors_using_iterator)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original(4, "42sp");

  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");

  my_vector.clear();
  original.clear();
  cr_assert(ft::equal(original.begin(), original.end(), my_vector.begin()));
}

Test(vector_erased, expected_size_eq_to_the_original)
{
  ft::vector<int> my_vector;
  std::vector<int> original(4, 42);

  my_vector.push_back(42);
  my_vector.push_back(42);
  my_vector.push_back(42);
  my_vector.push_back(42);

  original.erase(original.begin()+1);
  my_vector.erase(my_vector.begin()+1);
  cr_assert(my_vector.size() == original.size());
}

Test(vector_erased, expected_capacity_eq_the_original)
{
  ft::vector<int> my_vector;
  std::vector<int> original(4, 42);

  my_vector.push_back(42);
  my_vector.push_back(42);
  my_vector.push_back(42);
  my_vector.push_back(42);

  original.erase(original.begin()+1);
  my_vector.erase(my_vector.begin()+1);
  cr_assert(my_vector.capacity() == original.capacity());
}

Test(vector_erased, expected_same_return_as_the_original_vector)
{
  ft::vector<int> my_vector;
  std::vector<int> original;
  typename ft::vector<int>::iterator result;
  typename std::vector<int>::iterator expected;

  for (int i = 0; i < 10; ++i) {
    my_vector.push_back(i);
    original.push_back(i);
  }

  result = my_vector.erase(my_vector.begin()+2);
  expected = original.erase(original.begin()+2);

  cr_assert(*result == *expected);
}

Test(vector_erased, testing_overlaping_on_erase_method)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original;

  my_vector.push_back("42");
  my_vector.push_back("43");
  my_vector.push_back("44");
  my_vector.push_back("45");

  original.push_back("42");
  original.push_back("43");
  original.push_back("44");
  original.push_back("45");

  my_vector.erase(my_vector.begin()+1);
  original.erase(original.begin()+1);

  cr_assert(ft::equal(original.begin(), original.end(), my_vector.begin()));
}

Test(vector_erased, erased_last_element_and_expected_iterator_end)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original(4, "42sp");
  typename ft::vector<std::string>::iterator result;
  typename std::vector<std::string>::iterator expected;

  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");

  result = my_vector.erase(--my_vector.end());
  expected = original.erase(--original.end());

  cr_assert(result == my_vector.end() && expected == original.end());
}

Test(vector_erased, expected_the_same_sequence_as_the_original)
{
  ft::vector<int> my_vector;
  std::vector<int> original;

  for (int i = 0; i < 10; ++i) {
    my_vector.push_back(i);
    original.push_back(i);
  }

  my_vector.erase(my_vector.begin()+3);
  original.erase(original.begin()+3);

  cr_assert(ft::equal(original.begin(), original.end(), my_vector.begin()));
}

Test(vector_erased, test_when_last_and_first_are_eq_expected_the_same_iterator_returned)
{
  ft::vector<double> my_vector;
  std::vector<double> original;
  typename ft::vector<double>::iterator result;
  typename std::vector<double>::iterator expected;

  for (double i = 0; i < 10; ++i) {
    my_vector.push_back(i);
    original.push_back(i);
  }

  result = my_vector.erase(my_vector.begin()+2, my_vector.begin()+2);
  expected = original.erase(original.begin()+2, original.begin()+2);
  cr_assert(*result == *expected);
}

Test(vector_erased, test_when_last_eq_end_expected_the_size_eq_to_1)
{
  ft::vector<std::string> my_vector;

  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");

  my_vector.erase(my_vector.begin()+1, my_vector.end());
  cr_assert(my_vector.size() == 1);
}

Test(vector_erased, test_when_last_eq_end_expected_the_same_sequence_after_erase)
{
  ft::vector<int> my_vector;
  std::vector<int> original;

  for (int i = 0; i < 10; i++) {
    my_vector.push_back(i);
    original.push_back(i);
  }

  my_vector.erase(my_vector.begin()+4, my_vector.end());
  original.erase(original.begin()+4, original.end());
  cr_assert(ft::equal(original.begin(), original.end(), my_vector.begin()));
}

Test(vector_erased, test_last_diff_from_first_and_end_expected_the_same_sequence)
{
  ft::vector<int> my_vector;
  std::vector<int> original;

  for (int i = 0; i < 10; i++) {
    my_vector.push_back(i);
    original.push_back(i);
  }

  my_vector.erase(my_vector.begin()+2, my_vector.begin()+4);
  original.erase(original.begin()+2, original.begin()+4);
  cr_assert(ft::equal(original.begin(), original.end(), my_vector.begin()));
}

Test(vector_erased, test_last_diff_from_first_and_end_expected_the_same_size)
{
  ft::vector<int> my_vector;
  std::vector<int> original;

  for (int i = 0; i < 10; i++) {
    my_vector.push_back(i);
    original.push_back(i);
  }

  my_vector.erase(my_vector.begin()+2, my_vector.begin()+5);
  original.erase(original.begin()+2, original.begin()+5);
  cr_assert(my_vector.size() == original.size());
}

Test(vector_erased, test_last_diff_from_first_and_end_expected_the_same_returned_value)
{
  ft::vector<int> my_vector;
  std::vector<int> original;
  typename ft::vector<int>::iterator result;
  typename std::vector<int>::iterator expected;

  for (int i = 0; i < 10; i++) {
    my_vector.push_back(i);
    original.push_back(i);
  }

  result = my_vector.erase(my_vector.begin()+3, my_vector.begin()+5);
  expected = original.erase(original.begin()+3, original.begin()+5);
  cr_assert(*result == *expected);
}

Test(vector_resize, downsize_vector_to_size_eq_2)
{
  ft::vector<int> my_vector;
  std::vector<int> original(4, 10);

  my_vector.push_back(10);
  my_vector.push_back(10);
  my_vector.push_back(10);
  my_vector.push_back(10);

  my_vector.resize(2);
  original.resize(2);
  cr_assert(my_vector.size() == original.size());
}

Test(vector_resize, incresce_size_in_4_elements_expected_same_size_as_the_original_vector)
{
  ft::vector<int> my_vector;
  std::vector<int> original(4, 10);

  my_vector.push_back(10);
  my_vector.push_back(10);
  my_vector.push_back(10);
  my_vector.push_back(10);

  my_vector.resize(8);
  original.resize(8);
  cr_assert(my_vector.size() == original.size());
}

Test(vector_resize, incresce_size_in_4_elements_expected_same_capacity_as_the_original_vector)
{
  ft::vector<int> my_vector;
  std::vector<int> original(4, 10);

  my_vector.push_back(10);
  my_vector.push_back(10);
  my_vector.push_back(10);
  my_vector.push_back(10);

  my_vector.resize(8);
  original.resize(8);
  cr_assert(my_vector.capacity() == original.capacity());
}

Test(vector_resize, incresce_size_in_8_elements_expected_same_values_as_the_original)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original(4, "42sp");

  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");

  my_vector.resize(8);
  original.resize(8);
  cr_assert(ft::equal(original.begin(), original.end(), my_vector.begin()));
}

Test(vector_resize, dont_change_the_size_expected_anything_change)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original(4, "42sp");

  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");
  my_vector.push_back("42sp");

  my_vector.resize(4);
  original.resize(4);
  cr_assert(
      my_vector.size() == original.size()
      && my_vector.capacity() == original.capacity()
  );
}

Test(vector_insert, when_pos_eq_end_expected_same_return)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original;
  typename ft::vector<std::string>::iterator result;
  typename std::vector<std::string>::iterator expected;

  my_vector.push_back("42");
  my_vector.push_back("43");

  original.push_back("42");
  original.push_back("43");

  result = my_vector.insert(my_vector.end(), "44");
  expected = original.insert(original.end(), "44");
  cr_assert(*result == *expected);
}

Test(vector_insert, when_capacity_is_less_than_size_plus_one_expected_same_size)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original;

  my_vector.push_back("42");
  my_vector.push_back("44");

  original.push_back("42");
  original.push_back("44");

  my_vector.insert(my_vector.begin(), "43");
  original.insert(original.begin(), "43");
  cr_assert(my_vector.size() == original.size());
} 


Test(vector_insert, when_capacity_is_less_than_size_plus_one_expected_same_capacity)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original;

  my_vector.push_back("42");
  my_vector.push_back("44");

  original.push_back("42");
  original.push_back("44");

  my_vector.insert(my_vector.begin(), "43");
  original.insert(original.begin(), "43");
  cr_assert(my_vector.capacity() == original.capacity());
} 


Test(vector_insert, when_capacity_is_less_than_size_plus_one_expected_same_values)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original;
  typename ft::vector<std::string>::iterator test;

  my_vector.push_back("42");
  my_vector.push_back("44");

  original.push_back("42");
  original.push_back("44");

  my_vector.insert(my_vector.begin()+1, "43");
  original.insert(original.begin()+1, "43");
  cr_assert(ft::equal(original.begin(), original.end(), my_vector.begin()));
}

Test(vector_insert, when_capacity_is_less_than_size_plus_one_expected_same_return)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original;
  typename ft::vector<std::string>::iterator result, test;
  typename std::vector<std::string>::iterator expected;

  my_vector.push_back("42");
  my_vector.push_back("44");

  original.push_back("42");
  original.push_back("44");

  result = my_vector.insert(my_vector.begin()+1, "43");
  expected = original.insert(original.begin()+1, "43");
  cr_assert(*result == *expected);
}


Test(vector_insert, when_capacity_is_sufficient_to_insert_more_elements_expected_eq_to_original)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original;
  typename ft::vector<std::string>::iterator result;
  typename std::vector<std::string>::iterator expected;

  my_vector.push_back("42");
  my_vector.push_back("43");
  my_vector.push_back("44");
  my_vector.push_back("46");

  original.push_back("42");
  original.push_back("43");
  original.push_back("44");
  original.push_back("46");

  my_vector.insert(my_vector.begin()+3, "45");
  original.insert(original.begin()+3, "45");
  cr_assert(ft::equal(original.begin(), original.end(), my_vector.begin()));
}

Test(vector_insert, when_capacity_is_sufficient_to_insert_more_elements_expected_same_return)
{
  ft::vector<std::string> my_vector;
  std::vector<std::string> original;
  typename ft::vector<std::string>::iterator result;
  typename std::vector<std::string>::iterator expected;

  my_vector.push_back("42");
  my_vector.push_back("43");
  my_vector.push_back("44");
  my_vector.push_back("46");

  original.push_back("42");
  original.push_back("43");
  original.push_back("44");
  original.push_back("46");

  result = my_vector.insert(my_vector.begin()+3, "45");
  expected = original.insert(original.begin()+3, "45");
  cr_assert(*result == *expected);
}
