#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "iterator.hpp"
#include "type_traits.hpp"
#include "vector.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include "algorithms.hpp"
#include "doctest.h"

TEST_SUITE("vector")
{

  TEST_SUITE("Capacity") {
    TEST_CASE("expected_capacity_eq_2")
    {
      ft::vector<int> my_vector;
      ft::vector<int>::size_type expected, result;

      my_vector.push_back(1);
      my_vector.push_back(2);

      expected = 2;
      result = my_vector.capacity();
      CHECK_EQ(expected, result);
    }

    TEST_CASE("expected_capacity_eq_4")
    {
      ft::vector<int> my_vector;
      ft::vector<int>::size_type expected, result;

      my_vector.push_back(1);
      my_vector.push_back(2);
      my_vector.push_back(3);
      my_vector.push_back(4);

      expected = 4;
      result = my_vector.capacity();
      CHECK_EQ(result, expected);
    }

    TEST_CASE("expected_size_eq_0")
    {
      ft::vector<int> my_vector;
      ft::vector<int>::size_type expected;

      expected = 0;
      CHECK_EQ(my_vector.size(), expected);
    }

    TEST_CASE("expected_size_eq_20")
    {
      ft::vector<int> my_vector;
      ft::vector<int>::size_type expected, result;

      for (int i = 0; i < 20; ++i)
        my_vector.push_back(42);

      expected = 20;
      result = my_vector.size();
      CHECK_EQ(result, expected);
    }

    TEST_CASE("expected_true")
    {
      ft::vector<int> my_vector;

      CHECK_EQ(my_vector.empty(), true);
    }

    TEST_CASE("expected_false")
    {
      ft::vector<int> my_vector;

      my_vector.push_back(42);

      CHECK_FALSE(my_vector.empty());
    }

    TEST_CASE("expected_size_max_of_char")
    {
      ft::vector<char> my_vector;
      std::vector<char> original;

      CHECK_EQ(my_vector.max_size(), original.max_size());
    }


    TEST_CASE("expected_size_max_of_int")
    {
      ft::vector<int> my_vector;
      std::vector<int> original;

      CHECK_EQ(my_vector.max_size(), original.max_size());
    }

    TEST_CASE("expected_size_max_of_float")
    {
      ft::vector<float> my_vector;
      std::vector<float> original;

      CHECK_EQ(my_vector.max_size(), original.max_size());
    }


    TEST_CASE("expected_size_max_of_double")
    {
      ft::vector<double> my_vector;
      std::vector<double> original;

      CHECK_EQ(my_vector.max_size(), original.max_size());
    }

    TEST_CASE("expected_size_max_of_long_long_int")
    {
      ft::vector<long long int> my_vector;
      std::vector<long long int> original;

      CHECK_EQ(my_vector.max_size(), original.max_size());
    }

    TEST_CASE("expected_size_max_of_std_string")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original;

      CHECK_EQ(my_vector.max_size(), original.max_size());
    }
  } // end of suite capacity

  TEST_SUITE("Modifiers") {
    TEST_CASE("expected_all_values_from_iterator_eq_to_42")
    {
      ft::vector<int> my_vector;
      std::vector<int> original_vector(20, 42);
      ft::vector<int>::iterator result;
      std::vector<int>::iterator expected = original_vector.begin();

      for (int i = 0; i < 20; ++i)
        my_vector.push_back(42);

      result = my_vector.begin();

      CHECK_EQ(ft::equal(expected, original_vector.end(), result), true);
    }

    TEST_CASE("expected_all_values_from_const_iterator_eq_to_30")
    {
      ft::vector<int> my_vector;
      std::vector<int> const original_vector(20, 42);
      std::vector<int>::const_iterator expected = original_vector.begin();

      for (int i = 0; i < 20; i++)
        my_vector.push_back(42);

      CHECK_EQ(ft::equal(expected, original_vector.end(), my_vector.begin()), true);
    }


    TEST_CASE("expected_right_sequence_values_for_no_integral_types")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original(3, "42sp");
      ft::vector<std::string>::iterator result;

      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");

      CHECK_EQ(
          ft::equal(original.begin(), original.end(), my_vector.begin()), true
          );
    }

    TEST_CASE("expected_vectors_with_the_same_number_of_size")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original(2, "42sp");

      my_vector.push_back("42sp");
      my_vector.push_back("42sp");

      original.pop_back();
      my_vector.pop_back();

      CHECK_EQ(original.size(), my_vector.size());
    }

    TEST_CASE("expected_vectors_with_same_capacity")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original(2, "42sp");

      my_vector.push_back("42sp");
      my_vector.push_back("42sp");

      original.pop_back();
      my_vector.pop_back();

      CHECK_EQ(original.capacity(), my_vector.capacity());
    }

    TEST_CASE("expected_same_values_for_vectors_using_iterator")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original(4, "42sp");

      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");

      original.pop_back();
      my_vector.pop_back();

      CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
    }

    TEST_CASE("expected_same_values_for_vectors_using_reverse_iterator")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original(4, "42sp");

      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");

      original.pop_back();
      my_vector.pop_back();

      CHECK(ft::equal(original.rbegin(), original.rend(), my_vector.rbegin()));
    }

    TEST_CASE("expected_the_same_value_of_capacity")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original(4, "42sp");

      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");

      my_vector.clear();
      original.clear();
      CHECK_EQ(my_vector.capacity(), original.capacity());
    }

    TEST_CASE("expected_size_eq_0")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original(4, "42sp");

      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");

      my_vector.clear();
      original.clear();
      CHECK_EQ(my_vector.size(), original.size());
    }

    TEST_CASE("expected_same_values_for_vectors_using_iterator")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original(4, "42sp");

      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");

      my_vector.clear();
      original.clear();
      CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
    }

    TEST_CASE("expected_size_eq_to_the_original")
    {
      ft::vector<int> my_vector;
      std::vector<int> original(4, 42);

      my_vector.push_back(42);
      my_vector.push_back(42);
      my_vector.push_back(42);
      my_vector.push_back(42);

      original.erase(original.begin()+1);
      my_vector.erase(my_vector.begin()+1);
      CHECK_EQ(my_vector.size(), original.size());
    }

    TEST_CASE("expected_capacity_eq_the_original")
    {
      ft::vector<int> my_vector;
      std::vector<int> original(4, 42);

      my_vector.push_back(42);
      my_vector.push_back(42);
      my_vector.push_back(42);
      my_vector.push_back(42);

      original.erase(original.begin()+1);
      my_vector.erase(my_vector.begin()+1);
      CHECK_EQ(my_vector.capacity(), original.capacity());
    }

    TEST_CASE("expected_same_return_as_the_original_vector")
    {
      ft::vector<int> my_vector;
      std::vector<int> original;
      ft::vector<int>::iterator result;
      std::vector<int>::iterator expected;

      for (int i = 0; i < 10; ++i) {
        my_vector.push_back(i);
        original.push_back(i);
      }

      result = my_vector.erase(my_vector.begin()+2);
      expected = original.erase(original.begin()+2);

      CHECK_EQ(*result, *expected);
    }

    TEST_CASE("testing_overlaping_on_erase_method")
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

      CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
    }

    TEST_CASE("erased_last_element_and_expected_iterator_end")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original(4, "42sp");
      ft::vector<std::string>::iterator result;
      std::vector<std::string>::iterator expected;

      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");

      result = my_vector.erase(--my_vector.end());
      expected = original.erase(--original.end());

      CHECK_EQ(result, my_vector.end());
    }

    TEST_CASE("expected_the_same_sequence_as_the_original")
    {
      ft::vector<int> my_vector;
      std::vector<int> original;

      for (int i = 0; i < 10; ++i) {
        my_vector.push_back(i);
        original.push_back(i);
      }

      my_vector.erase(my_vector.begin()+3);
      original.erase(original.begin()+3);

      CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
    }

    TEST_CASE("test_when_last_and_first_are_eq_expected_the_same_iterator_returned")
    {
      ft::vector<double> my_vector;
      std::vector<double> original;
      ft::vector<double>::iterator result;
      std::vector<double>::iterator expected;

      for (double i = 0; i < 10; ++i) {
        my_vector.push_back(i);
        original.push_back(i);
      }

      result = my_vector.erase(my_vector.begin()+2, my_vector.begin()+2);
      expected = original.erase(original.begin()+2, original.begin()+2);
      CHECK_EQ(*result, *expected);
    }

    TEST_CASE("test_when_last_eq_end_expected_the_size_eq_to_1")
    {
      ft::vector<std::string> my_vector;

      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");

      my_vector.erase(my_vector.begin()+1, my_vector.end());
      CHECK_EQ(my_vector.size(), 1);
    }

    TEST_CASE("test_when_last_eq_end_expected_the_same_sequence_after_erase")
    {
      ft::vector<int> my_vector;
      std::vector<int> original;

      for (int i = 0; i < 10; i++) {
        my_vector.push_back(i);
        original.push_back(i);
      }

      my_vector.erase(my_vector.begin()+4, my_vector.end());
      original.erase(original.begin()+4, original.end());
      CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
    }

    TEST_CASE("test_last_diff_from_first_and_end_expected_the_same_sequence")
    {
      ft::vector<int> my_vector;
      std::vector<int> original;

      for (int i = 0; i < 10; i++) {
        my_vector.push_back(i);
        original.push_back(i);
      }

      my_vector.erase(my_vector.begin()+2, my_vector.begin()+4);
      original.erase(original.begin()+2, original.begin()+4);
      CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
    }

    TEST_CASE("test_last_diff_from_first_and_end_expected_the_same_size")
    {
      ft::vector<int> my_vector;
      std::vector<int> original;

      for (int i = 0; i < 10; i++) {
        my_vector.push_back(i);
        original.push_back(i);
      }

      my_vector.erase(my_vector.begin()+2, my_vector.begin()+5);
      original.erase(original.begin()+2, original.begin()+5);
      CHECK_EQ(my_vector.size(), original.size());
    }

    TEST_CASE("test_last_diff_from_first_and_end_expected_the_same_returned_value")
    {
      ft::vector<int> my_vector;
      std::vector<int> original;
      ft::vector<int>::iterator result;
      std::vector<int>::iterator expected;

      for (int i = 0; i < 10; i++) {
        my_vector.push_back(i);
        original.push_back(i);
      }

      result = my_vector.erase(my_vector.begin()+3, my_vector.begin()+5);
      expected = original.erase(original.begin()+3, original.begin()+5);
      CHECK_EQ(*result, *expected);
    }

    TEST_CASE("downsize_vector_to_size_eq_2")
    {
      ft::vector<int> my_vector;
      std::vector<int> original(4, 10);

      my_vector.push_back(10);
      my_vector.push_back(10);
      my_vector.push_back(10);
      my_vector.push_back(10);

      my_vector.resize(2);
      original.resize(2);
      CHECK_EQ(my_vector.size(), original.size());
    }

    TEST_CASE("incresce_size_in_4_elements_expected_same_size_as_the_original_vector")
    {
      ft::vector<int> my_vector;
      std::vector<int> original(4, 10);

      my_vector.push_back(10);
      my_vector.push_back(10);
      my_vector.push_back(10);
      my_vector.push_back(10);

      my_vector.resize(8);
      original.resize(8);
      CHECK_EQ(my_vector.size(), original.size());
    }

    TEST_CASE("incresce_size_in_4_elements_expected_same_capacity_as_the_original_vector")
    {
      ft::vector<int> my_vector;
      std::vector<int> original(4, 10);

      my_vector.push_back(10);
      my_vector.push_back(10);
      my_vector.push_back(10);
      my_vector.push_back(10);

      my_vector.resize(8);
      original.resize(8);
      CHECK_EQ(my_vector.capacity(), original.capacity());
    }

    TEST_CASE("incresce_size_in_8_elements_expected_same_values_as_the_original")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original(4, "42sp");

      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");

      my_vector.resize(8);
      original.resize(8);
      CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
    }

    TEST_CASE("dont_change_the_size_expected_anything_change")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original(4, "42sp");

      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");

      my_vector.resize(4);
      original.resize(4);
      CHECK_EQ(
          my_vector.size(), original.size()
      );
    }

    TEST_CASE("dont_change_the_capacity_expected_anything_change")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original(4, "42sp");

      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");
      my_vector.push_back("42sp");

      my_vector.resize(4);
      original.resize(4);
      CHECK_EQ(
          my_vector.capacity(), original.capacity()
      );
    }


    TEST_CASE("when_pos_eq_end_expected_same_return")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original;
      ft::vector<std::string>::iterator result;
      std::vector<std::string>::iterator expected;

      my_vector.push_back("42");
      my_vector.push_back("43");

      original.push_back("42");
      original.push_back("43");

      result = my_vector.insert(my_vector.end(), "44");
      expected = original.insert(original.end(), "44");
      CHECK_EQ(*result, *expected);
    }

    TEST_CASE("when_capacity_is_less_than_size_plus_one_expected_same_size")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original;

      my_vector.push_back("42");
      my_vector.push_back("44");

      original.push_back("42");
      original.push_back("44");

      my_vector.insert(my_vector.begin(), "43");
      original.insert(original.begin(), "43");
      CHECK_EQ(my_vector.size(), original.size());
    } 


    TEST_CASE("when_capacity_is_less_than_size_plus_one_expected_same_capacity")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original;

      my_vector.push_back("42");
      my_vector.push_back("44");

      original.push_back("42");
      original.push_back("44");

      my_vector.insert(my_vector.begin(), "43");
      original.insert(original.begin(), "43");
      CHECK_EQ(my_vector.capacity(), original.capacity());
    } 


    TEST_CASE("when_capacity_is_less_than_size_plus_one_expected_same_values")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original;
      ft::vector<std::string>::iterator test;

      my_vector.push_back("42");
      my_vector.push_back("44");

      original.push_back("42");
      original.push_back("44");

      my_vector.insert(my_vector.begin()+1, "43");
      original.insert(original.begin()+1, "43");
      CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
    }

    TEST_CASE("when_capacity_is_less_than_size_plus_one_expected_same_return")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original;
      ft::vector<std::string>::iterator result, test;
      std::vector<std::string>::iterator expected;

      my_vector.push_back("42");
      my_vector.push_back("44");

      original.push_back("42");
      original.push_back("44");

      result = my_vector.insert(my_vector.begin()+1, "43");
      expected = original.insert(original.begin()+1, "43");
      CHECK_EQ(*result, *expected);
    }


    TEST_CASE("when_capacity_is_sufficient_to_insert_more_elements_expected_eq_to_original")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original;
      ft::vector<std::string>::iterator result;
      std::vector<std::string>::iterator expected;

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
      CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
    }

    TEST_CASE("when_capacity_is_sufficient_to_insert_more_elements_expected_same_return")
    {
      ft::vector<std::string> my_vector;
      std::vector<std::string> original;
      ft::vector<std::string>::iterator result;
      std::vector<std::string>::iterator expected;

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
      CHECK_EQ(*result, *expected);
    }

    TEST_CASE("expected_same_address_of_iterator")
    {
      ft::vector<std::string> my_vector;
      ft::vector<std::string>::iterator result;

      my_vector.push_back("42");
      my_vector.push_back("43");
      my_vector.push_back("44");
      my_vector.push_back("46");

      result = my_vector.insert(my_vector.begin()+3, "44");
      CHECK_EQ(result, my_vector.begin()+3);
    }

    TEST_CASE("expected_same_address_of_iterator_2")
    {
      ft::vector<std::string> my_vector;
      ft::vector<std::string>::iterator result;

      my_vector.push_back("42");
      my_vector.push_back("43");
      my_vector.push_back("44");
      my_vector.push_back("46");

      result = my_vector.insert(my_vector.begin()+1, "44");
      CHECK_EQ(result, my_vector.begin()+1);
    }

    TEST_CASE("expected_size_eq_the_original_vector")
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

      my_vector.insert(my_vector.begin()+2, 4, "43.5");
      original.insert(original.begin()+2, 4, "43.5");

      CHECK_EQ(original.size(), my_vector.size());
    }


    TEST_CASE("expected_same_capacity_as_the_original")
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

      my_vector.insert(my_vector.begin()+2, 4, "43.5");
      original.insert(original.begin()+2, 4, "43.5");

      CHECK_EQ(original.capacity(), my_vector.capacity());
    }

    TEST_CASE("expected_same_sequence_of_the_values_as_the_original")
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

      my_vector.insert(my_vector.begin()+2, 4, "43.5");
      original.insert(original.begin()+2, 4, "43.5");

      CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
    }

    TEST_CASE("expected_same_sequence_of_the_values_as_the_original_2")
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

      my_vector.insert(--my_vector.end(), 10, "44.5");
      original.insert(--original.end(), 10, "44.5");

      CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
    }

    TEST_CASE("expected_the_same_size")
    {
      ft::vector<std::string> my_vector;
      ft::vector<std::string> m_vector;

      m_vector.push_back("42");
      m_vector.push_back("43");
      m_vector.push_back("43.5");
      m_vector.push_back("43.5");
      m_vector.push_back("43.5");
      m_vector.push_back("43.5");
      m_vector.push_back("43.5");
      m_vector.push_back("44");
      m_vector.push_back("45");

      my_vector.push_back("42");
      my_vector.push_back("43");
      my_vector.push_back("44");
      my_vector.push_back("45");

      my_vector.insert(my_vector.begin()+2, m_vector.begin()+2, m_vector.end()-2);

      CHECK_EQ(my_vector.size(), m_vector.size());
    }


    TEST_CASE("expected_the_same_capacity")
    {
      ft::vector<std::string> my_vector;
      ft::vector<std::string> m_vector;

      m_vector.push_back("42");
      m_vector.push_back("43");
      m_vector.push_back("43.5");
      m_vector.push_back("43.5");
      m_vector.push_back("43.5");
      m_vector.push_back("43.5");
      m_vector.push_back("43.5");
      m_vector.push_back("44");
      m_vector.push_back("45");

      my_vector.push_back("42");
      my_vector.push_back("43");
      my_vector.push_back("44");
      my_vector.push_back("45");

      my_vector.insert(my_vector.begin()+2, m_vector.begin()+2, m_vector.end()-2);

      CHECK_EQ(my_vector.capacity(), m_vector.capacity());
    }

    TEST_CASE("expected_the_same_values")
    {
      ft::vector<std::string> my_vector;
      ft::vector<std::string> m_vector;
      std::vector<std::string> original;
      std::vector<std::string> m_original;

      m_vector.push_back("42");
      m_vector.push_back("43");
      m_vector.push_back("43.5");
      m_vector.push_back("43.5");
      m_vector.push_back("43.5");
      m_vector.push_back("43.5");
      m_vector.push_back("43.5");
      m_vector.push_back("44");
      m_vector.push_back("45");

      my_vector.push_back("42");
      my_vector.push_back("43");
      my_vector.push_back("44");
      my_vector.push_back("45");

      original.push_back("42");
      original.push_back("43");
      original.push_back("44");
      original.push_back("45");

      m_original.push_back("42");
      m_original.push_back("43");
      m_original.push_back("43.5");
      m_original.push_back("43.5");
      m_original.push_back("43.5");
      m_original.push_back("43.5");
      m_original.push_back("43.5");
      m_original.push_back("44");
      m_original.push_back("45");

      my_vector.insert(my_vector.begin()+2, m_vector.begin()+2, m_vector.end()-2);
      original.insert(original.begin()+2, m_original.begin()+2, m_original.end()-2);
      CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
    }

    TEST_CASE("expected_the_same_size_with_integral")
    {
      ft::vector<unsigned int> my_vector;
      ft::vector<unsigned int> m_vector;

      m_vector.push_back(42);
      m_vector.push_back(43);
      m_vector.push_back(43);
      m_vector.push_back(43);
      m_vector.push_back(43);
      m_vector.push_back(43);
      m_vector.push_back(43);
      m_vector.push_back(44);
      m_vector.push_back(45);

      my_vector.push_back(42);
      my_vector.push_back(43);
      my_vector.push_back(44);
      my_vector.push_back(45);

      my_vector.insert(my_vector.begin()+2, m_vector.begin()+2, m_vector.end()-2);

      CHECK_EQ(my_vector.size(), m_vector.size());
    }


    TEST_CASE("expected_the_same_capacity_with_integral")
    {
      ft::vector<unsigned int> my_vector;
      ft::vector<unsigned int> m_vector;

      m_vector.push_back(42);
      m_vector.push_back(43);
      m_vector.push_back(43);
      m_vector.push_back(43);
      m_vector.push_back(43);
      m_vector.push_back(43);
      m_vector.push_back(43);
      m_vector.push_back(44);
      m_vector.push_back(45);

      my_vector.push_back(42);
      my_vector.push_back(43);
      my_vector.push_back(44);
      my_vector.push_back(45);

      my_vector.insert(my_vector.begin()+2, 5, 43);

      CHECK_EQ(my_vector.capacity(), m_vector.capacity());
    }

    TEST_CASE("expected_the_same_values_with_integral")
    {
      ft::vector<unsigned int> my_vector;
      ft::vector<unsigned int> m_vector;
      std::vector<unsigned int> original;
      std::vector<unsigned int> m_original;

      m_vector.push_back(42);
      m_vector.push_back(43);
      m_vector.push_back(43);
      m_vector.push_back(43);
      m_vector.push_back(43);
      m_vector.push_back(43);
      m_vector.push_back(43);
      m_vector.push_back(44);
      m_vector.push_back(45);

      my_vector.push_back(42);
      my_vector.push_back(43);
      my_vector.push_back(44);
      my_vector.push_back(45);

      original.push_back(42);
      original.push_back(43);
      original.push_back(44);
      original.push_back(45);

      m_original.push_back(42);
      m_original.push_back(43);
      m_original.push_back(43);
      m_original.push_back(43);
      m_original.push_back(43);
      m_original.push_back(43);
      m_original.push_back(43);
      m_original.push_back(44);
      m_original.push_back(45);

      my_vector.insert(my_vector.begin()+2, 5, 43);
      original.insert(original.begin()+2, 5, 43);
      CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
    }
  }// end of suite Modifiers
}
