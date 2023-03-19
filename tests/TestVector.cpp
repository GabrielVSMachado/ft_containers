#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <cstdlib>
#include <string>
#include "iterator.hpp"
#include "type_traits.hpp"
#include "vector.hpp"
#include <vector>
#include "algorithms.hpp"
#include "doctest.h"

TEST_SUITE("Capacity")
{
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

  TEST_CASE("expected_exception_std::length_error")
  {
    ft::vector<int> my_vector;

    CHECK_THROWS_AS(
      my_vector.reserve(my_vector.max_size() + 1), std::length_error
    );
  }

  TEST_CASE("expected_do_nothing_with_capacity")
  {
    ft::vector<int> my_vector;

    my_vector.reserve(0);

    CHECK_EQ(my_vector.capacity(), 0);
  }

  TEST_CASE("expected_capacity_eq_3")
  {
    ft::vector<int> my_vector;

    my_vector.push_back(42);
    my_vector.push_back(43);

    my_vector.reserve(3);

    CHECK_EQ(my_vector.capacity(), 3);
  }

  TEST_CASE("expected_same_size_before_reserve")
  {
    ft::vector<std::string> my_vector;

    my_vector.push_back("42");
    my_vector.push_back("43");

    my_vector.reserve(4);
    CHECK_EQ(my_vector.size(), 2);
  }

  TEST_CASE("expected_same_values_before_reserve")
  {
    ft::vector<std::string> my_vector;
    std::vector<std::string> original;

    my_vector.push_back("42");
    my_vector.push_back("43");

    original.push_back("42");
    original.push_back("43");

    my_vector.reserve(4);
    CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
  }
} // end of suite capacity

TEST_SUITE("push_back_vector_method")
{
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
}

TEST_SUITE("pop_back_vector_method")
{
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

    CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
  }
}

TEST_SUITE("clear_vector_method")
{
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
}

TEST_SUITE("erase_vector_method")
{
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
    std::vector<std::string> original;
    ft::vector<std::string>::iterator result;
    std::vector<std::string>::iterator expected;

    my_vector.push_back("43sp");
    my_vector.push_back("44sp");
    my_vector.push_back("45sp");
    my_vector.push_back("46sp");

    original.push_back("43sp");
    original.push_back("44sp");
    original.push_back("45sp");
    original.push_back("46sp");


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
}

TEST_SUITE("resize_vector_method")
{
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
    ft::vector<int> my_vector(4, 10);
    std::vector<int> original(4, 10);

    my_vector.resize(8);
    original.resize(8);

    CHECK_EQ(my_vector.size(), original.size());
  }

  TEST_CASE("incresce_size_in_4_elements_expected_same_capacity_as_the_original_vector")
  {
    ft::vector<int> my_vector(4, 10);
    std::vector<int> original(4, 10);

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
}

TEST_SUITE("insert_vector_method")
{
  TEST_CASE("test_first_overloadingt_when_values_are_unintialized")
  {
    ft::vector<std::string> my_vector;

    my_vector.insert(my_vector.end(), "42");
    CHECK_EQ(*my_vector.begin(), "42");
  }

  TEST_CASE("test_first_overloading_when_values_are_unintialized_2") {
    ft::vector<std::string> my_vector;
    std::vector<std::string> original(1, "42");

    original.insert(original.end(), "43");
    my_vector.insert(my_vector.end(), "42");
    my_vector.insert(my_vector.end(), "43");
    CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
  }

  TEST_CASE("test_first_overloading_when_values_are_unintialized_insert_between")
  {
    ft::vector<std::string> my_vector;
    std::vector<std::string> original(1, "41");

    original.insert(original.end(), "42");
    original.insert(original.end(), "43");
    my_vector.insert(my_vector.end(), "41");
    my_vector.insert(my_vector.begin()+1, "42");
    my_vector.insert(my_vector.end(), "43");
    CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
  }

  TEST_CASE("test_first_overloading_when_capacity_is_sufficient")
  {
    ft::vector<std::string> my_vector;
    std::vector<std::string> original;

    original.push_back("41");
    original.push_back("42");
    original.push_back("43");
    original.push_back("44");
    original.push_back("45");

    my_vector.reserve(5);
    my_vector.insert(my_vector.end(), "41");
    my_vector.insert(my_vector.end(), "42");
    my_vector.insert(my_vector.end(), "44");
    my_vector.insert(my_vector.end(), "45");
    my_vector.insert(my_vector.begin()+2, "43");
    CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
  }

  TEST_CASE("test_first_overloading_expected_same_return")
  {
    ft::vector<std::string> my_vector;
    std::vector<std::string> original(10, "42");
    ft::vector<std::string>::iterator result;
    std::vector<std::string>::iterator expected;

    my_vector.reserve(10);
    my_vector.insert(my_vector.end(), "42");
    my_vector.insert(my_vector.end(), "42");
    my_vector.insert(my_vector.end(), "42");
    my_vector.insert(my_vector.end(), "42");
    my_vector.insert(my_vector.end(), "42");
    my_vector.insert(my_vector.end(), "42");
    my_vector.insert(my_vector.end(), "42");
    my_vector.insert(my_vector.end(), "42");
    my_vector.insert(my_vector.end(), "42");
    my_vector.insert(my_vector.end(), "42");
    expected = original.insert(original.begin()+7, "43");
    result = my_vector.insert(my_vector.begin()+7, "43");
    CHECK_EQ(*expected, *result);
  }

  TEST_CASE("test_second_overloading_when_values_are_unintialized")
  {
    ft::vector<int> my_vector;
    std::vector<int> original(10, 42);

    my_vector.insert(my_vector.end(), 10, 42);
    CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
  }

  TEST_CASE("test_second_overloading_expected_same_capacity")
  {
    ft::vector<std::string> my_vector;
    std::vector<std::string> original;

    original.insert(original.end(), "42");
    original.insert(original.end(), "43");
    original.insert(original.end(), "44");
    original.insert(original.end(), "45");
    original.insert(original.end(), "46");
    original.insert(original.end(), "47");
    original.insert(original.end(), "48");

    my_vector.insert(my_vector.end(), "42");
    my_vector.insert(my_vector.end(), "43");
    my_vector.insert(my_vector.end(), "44");
    my_vector.insert(my_vector.end(), "45");
    my_vector.insert(my_vector.end(), "46");
    my_vector.insert(my_vector.end(), "47");
    my_vector.insert(my_vector.end(), "48");

    my_vector.insert(my_vector.begin()+4, 11,"1234567");
    original.insert(original.begin()+4, 11,"1234567");
    CHECK_EQ(my_vector.capacity(), original.capacity());
  }

  TEST_CASE("test_second_overloading_expected_same_size")
  {
    ft::vector<std::string> my_vector;
    std::vector<std::string> original;

    original.insert(original.end(), "42");
    original.insert(original.end(), "43");
    original.insert(original.end(), "44");
    original.insert(original.end(), "45");
    original.insert(original.end(), "46");
    original.insert(original.end(), "47");
    original.insert(original.end(), "48");

    my_vector.insert(my_vector.end(), "42");
    my_vector.insert(my_vector.end(), "43");
    my_vector.insert(my_vector.end(), "44");
    my_vector.insert(my_vector.end(), "45");
    my_vector.insert(my_vector.end(), "46");
    my_vector.insert(my_vector.end(), "47");
    my_vector.insert(my_vector.end(), "48");

    my_vector.insert(my_vector.begin()+4, 20,"1234567");
    original.insert(original.begin()+4, 20,"1234567");
    CHECK_EQ(my_vector.size(), original.size());
  }

  TEST_CASE("test_second_overloading_expected_same_values")
  {
    ft::vector<std::string> my_vector;
    std::vector<std::string> original;

    original.insert(original.end(), "42");
    original.insert(original.end(), "43");
    original.insert(original.end(), "44");
    original.insert(original.end(), "45");
    original.insert(original.end(), "46");
    original.insert(original.end(), "47");
    original.insert(original.end(), "48");

    my_vector.insert(my_vector.end(), "42");
    my_vector.insert(my_vector.end(), "43");
    my_vector.insert(my_vector.end(), "44");
    my_vector.insert(my_vector.end(), "45");
    my_vector.insert(my_vector.end(), "46");
    my_vector.insert(my_vector.end(), "47");
    my_vector.insert(my_vector.end(), "48");

    my_vector.insert(my_vector.begin()+4, 10, "1234567");
    original.insert(original.begin()+4, 10, "1234567");
    CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
  }

  TEST_CASE("test_second_overloading_expected_same_values_without_reallocate")
  {
    ft::vector<std::string> my_vector;
    std::vector<std::string> original;

    original.insert(original.end(), 10, "42");

    my_vector.reserve(10);

    my_vector.insert(my_vector.end(), 10, "42");
    CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
  }

  TEST_CASE("test_third_overloading_expected_same_size_as_original")
  {
    ft::vector<int> my_vector;
    std::vector<int> original;

    srand(time(NULL));
    for (size_t i = 0; i < 6; i++) {
      original.push_back(rand() % 50);
    }

    my_vector.insert(my_vector.begin(), original.begin(), original.end());
    CHECK_EQ(original.size(), my_vector.size());
  }

  std::string itoa(int n) { std::stringstream s; s << n; return s.str();}

  TEST_CASE("test_third_overloading_expected_same_capacity_as_original")
  {
    ft::vector<std::string> my_vector;
    std::vector<std::string> original;
    std::vector<std::string> expected;

    srand(time(NULL));
    for (size_t i = 0; i < 6; i++) {
      original.insert(original.end(), itoa(rand() % 50));
    }

    my_vector.insert(my_vector.begin(), original.begin(), original.end());
    expected.insert(expected.begin(), original.begin(), original.end());
    CHECK_EQ(expected.capacity(), my_vector.capacity());
  }

  TEST_CASE("test_first_overloading_expected_same_capacity_as_original")
  {
    ft::vector<std::string> my_vector;
    std::vector<std::string> original;
    std::vector<std::string> expected;

    srand(time(NULL));
    for (size_t i = 0; i < 6; i++) {
      original.insert(original.end(), itoa(rand() % 50));
      my_vector.insert(my_vector.end(), itoa(rand() % 50));
    }
    CHECK_EQ(my_vector.capacity(), original.capacity());
  }

  TEST_CASE("test_third_overloading_expected_same_values")
  {
    ft::vector<std::string> my_vector;
    std::vector<std::string> original;

    srand(time(NULL));
    for (size_t i = 0; i < 50; i++) {
      original.insert(original.end(), itoa(rand() % 50));
    }

    my_vector.reserve(100);

    my_vector.insert(my_vector.begin(), original.begin(), original.end());
    CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
  }
}

TEST_SUITE("swap_vector_method")
{
  TEST_CASE("expected_the_capacity_of_original_into_myvector")
  {
    ft::vector<std::string> my_vector;
    ft::vector<std::string> my_vector2;
    ft::vector<std::string> original;

    my_vector.push_back("42");
    my_vector.push_back("43");
    my_vector.push_back("44");
    my_vector.push_back("45");

    my_vector2.push_back("42");
    my_vector2.push_back("43");
    my_vector2.push_back("44");
    my_vector2.push_back("45");

    original.push_back("46");
    original.push_back("47");
    original.push_back("48");
    original.push_back("49");

    original.swap(my_vector);
    CHECK_EQ(original.capacity(), my_vector2.capacity());
  }

  TEST_CASE("expected_the_size_of_original_into_myvector")
  {
    ft::vector<std::string> my_vector;
    ft::vector<std::string> my_vector2;
    ft::vector<std::string> original;

    my_vector.push_back("42");
    my_vector.push_back("43");
    my_vector.push_back("44");
    my_vector.push_back("45");

    my_vector2.push_back("42");
    my_vector2.push_back("43");
    my_vector2.push_back("44");
    my_vector2.push_back("45");

    original.push_back("46");
    original.push_back("47");
    original.push_back("48");
    original.push_back("49");

    original.swap(my_vector);
    CHECK_EQ(original.size(), my_vector2.size());
  }

  TEST_CASE("expected_the_same_values_of_original_into_myvector")
  {
    ft::vector<std::string> my_vector;
    ft::vector<std::string> my_vector2;
    ft::vector<std::string> original;

    my_vector.push_back("42");
    my_vector.push_back("43");
    my_vector.push_back("44");
    my_vector.push_back("45");

    my_vector2.push_back("42");
    my_vector2.push_back("43");
    my_vector2.push_back("44");
    my_vector2.push_back("45");

    original.push_back("46");
    original.push_back("47");
    original.push_back("48");
    original.push_back("49");

    original.swap(my_vector);
    CHECK(ft::equal(original.begin(), original.end(), my_vector2.begin()));
  }
}

TEST_SUITE("Acess_methods")
{
  TEST_CASE("at_method_expected_exception_std::out_of_rage")
  {
    ft::vector<int> my_vector;

    my_vector.push_back(42);
    my_vector.push_back(43);
    my_vector.push_back(44);
    my_vector.push_back(45);
    my_vector.push_back(46);

    CHECK_THROWS_AS(my_vector.at(100000), std::out_of_range);
  }

  TEST_CASE("at_method_expected_reference_value_42")
  {
    ft::vector<int> my_vector;

    my_vector.push_back(46);
    my_vector.push_back(45);
    my_vector.push_back(44);
    my_vector.push_back(43);
    my_vector.push_back(42);

    CHECK_EQ(my_vector.at(4), 42);
  }

  TEST_CASE("at_method_expected_str_42")
  {
    ft::vector<std::string> my_vector;

    my_vector.push_back("46");
    my_vector.push_back("45");
    my_vector.push_back("44");
    my_vector.push_back("43");
    my_vector.push_back("42");

    CHECK_EQ(my_vector.at(4), "42");
  }

  TEST_CASE("at_method_expected_42_on_43_position")
  {
    ft::vector<int> my_vector;

    my_vector.push_back(46);
    my_vector.push_back(45);
    my_vector.push_back(44);
    my_vector.push_back(43);
    my_vector.push_back(42);

    my_vector.at(3) = 42;
    CHECK_EQ(my_vector.at(3), 42);
  }

  TEST_CASE("data_method_expected_same_values")
  {
    ft::vector<std::string> my_vector;
    std::vector<std::string> original;
    ft::vector<std::string>::pointer p;
    std::vector<std::string>::pointer op;

    my_vector.push_back("42");
    my_vector.push_back("43");
    my_vector.push_back("44");
    my_vector.push_back("45");
    my_vector.push_back("46");

    original.push_back("42");
    original.push_back("43");
    original.push_back("44");
    original.push_back("45");
    original.push_back("46");

    p = my_vector.data();
    op = original.data();
    CHECK_EQ(*(p + 3), *(op + 3));
  }
}

TEST_SUITE("assign")
{

  TEST_CASE("test_destroy_when_lenght_is_less_than_current_size")
  {
    ft::vector<std::string> my_vector(10, "42");
    std::vector<std::string> original(10, "43");

    my_vector.assign(original.begin(), original.begin()+4);
    original.assign(my_vector.begin(), my_vector.begin()+4);
    CHECK_EQ(original.size(), my_vector.size());
  }

  TEST_CASE("test_destroy_when_lenght_is_less_than_current_size_first_overloagind")
  {
    ft::vector<std::string> my_vector(10, "42");
    std::vector<std::string> original(10, "43");

    my_vector.assign(4, "42");
    original.assign(4, "42");
    CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
  }

  TEST_CASE("expected_exception_std::length_error")
  {
    ft::vector<std::string> my_vector;

    CHECK_THROWS_AS(
      my_vector.assign(my_vector.max_size() + 1, "42"), std::length_error
    );
  }

  TEST_CASE("expected_same_capacity_before_and_after")
  {
    ft::vector<int> my_vector;
    ft::vector<int>::size_type beforeCapacity, afterCapacity;

    my_vector.push_back(42);
    my_vector.push_back(43);
    my_vector.push_back(44);
    my_vector.push_back(45);

    beforeCapacity = my_vector.capacity();
    my_vector.assign(4, 42);
    afterCapacity = my_vector.capacity();
    CHECK_EQ(beforeCapacity, afterCapacity);
  }

  TEST_CASE("expected_same_size")
  {
    ft::vector<int> my_vector;
    ft::vector<int>::size_type beforeSize, afterSize;

    my_vector.push_back(42);
    my_vector.push_back(43);
    my_vector.push_back(44);
    my_vector.push_back(45);

    beforeSize = my_vector.size();
    my_vector.assign(4, 42);
    afterSize = my_vector.size();
    CHECK_EQ(beforeSize, afterSize);
  }

  TEST_CASE("expected_size_eq_10")
  {
    ft::vector<std::string> my_vector;

    my_vector.push_back("42");
    my_vector.push_back("43");
    my_vector.push_back("44");
    my_vector.push_back("45");

    my_vector.assign(10, "42");
    CHECK_EQ(10, my_vector.size());
  }

  TEST_CASE("expected_capacity_eq_10")
  {
    ft::vector<std::string> my_vector;

    my_vector.push_back("42");
    my_vector.push_back("43");
    my_vector.push_back("44");
    my_vector.push_back("45");

    my_vector.assign(10, "42");
    CHECK_EQ(10, my_vector.capacity());
  }

  TEST_CASE("expected_same_values_after_assign")
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


    my_vector.assign(10, "42");
    original.assign(10, "42");
    CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
  }

  TEST_CASE("assert_with_range_expected_same_capacity")
  {
    ft::vector<int> original;
    std::vector<int> o2(11, 42);

    original.push_back(41);
    original.push_back(42);
    original.push_back(43);
    original.push_back(44);

    original.assign(o2.begin(), o2.end());
    CHECK_EQ(original.capacity(), o2.capacity());
  }

  TEST_CASE("expected_same_size")
  {
    ft::vector<int> original;
    std::vector<int> o2(12, 42);

    original.push_back(41);
    original.push_back(42);
    original.push_back(43);
    original.push_back(44);

    original.assign(o2.begin(), o2.end());
    CHECK_EQ(original.size(), o2.size());
  }

  TEST_CASE("expected_same_values")
  {
    ft::vector<int> original;
    std::vector<int> o2(10, 42);

    original.push_back(41);
    original.push_back(42);
    original.push_back(43);
    original.push_back(44);

    original.assign(o2.begin(), o2.end());
    CHECK(ft::equal(o2.begin(), o2.end(), original.begin()));
  }
}

TEST_SUITE("get_allocator")
{
  TEST_CASE("expected_not_failed")
  {
    ft::vector<std::string> my_vector;
    my_vector.get_allocator();
    bool result = ft::is_same<ft::vector<std::string>::allocator_type, std::allocator<std::string> >::value;
    CHECK_EQ(result, true);
  }
}

TEST_SUITE("operator=")
{
  TEST_CASE("expected_same_size_integral_type")
  {
    ft::vector<int> my_vector;
    std::vector<int> original(4, 42);
    ft::vector<int> my_vector2;
    std::vector<int> original2(7, 42);

    my_vector.push_back(42);
    my_vector.push_back(42);
    my_vector.push_back(42);
    my_vector.push_back(42);


    my_vector2.push_back(42);
    my_vector2.push_back(42);
    my_vector2.push_back(42);
    my_vector2.push_back(42);
    my_vector2.push_back(42);
    my_vector2.push_back(42);
    my_vector2.push_back(42);

    my_vector = my_vector2;
    original = original2;
    CHECK_EQ(original.size(), my_vector.size());
  }

  TEST_CASE("expected_same_capacity_integral_type")
  {
    ft::vector<int> my_vector;
    std::vector<int> original(4, 42);
    ft::vector<int> my_vector2;
    std::vector<int> original2(7, 42);

    my_vector.push_back(42);
    my_vector.push_back(42);
    my_vector.push_back(42);
    my_vector.push_back(42);


    my_vector2.push_back(42);
    my_vector2.push_back(42);
    my_vector2.push_back(42);
    my_vector2.push_back(42);
    my_vector2.push_back(42);
    my_vector2.push_back(42);
    my_vector2.push_back(42);

    my_vector = my_vector2;
    original = original2;
    CHECK_EQ(original.capacity(), my_vector.capacity());
  }

  TEST_CASE("expected_same_values_integral_type")
  {
    ft::vector<int> my_vector;
    std::vector<int> original(4, 42);
    ft::vector<int> my_vector2;
    std::vector<int> original2;

    my_vector.push_back(42);
    my_vector.push_back(43);
    my_vector.push_back(44);
    my_vector.push_back(45);


    my_vector2.push_back(42);
    my_vector2.push_back(43);
    my_vector2.push_back(45);
    my_vector2.push_back(50);
    my_vector2.push_back(45);
    my_vector2.push_back(53);
    my_vector2.push_back(57);


    original2.push_back(42);
    original2.push_back(43);
    original2.push_back(45);
    original2.push_back(50);
    original2.push_back(45);
    original2.push_back(53);
    original2.push_back(57);

    my_vector = my_vector2;
    original = original2;
    CHECK(ft::equal(original.begin(), original.end(), my_vector.begin()));
  }
}

TEST_SUITE("boolean_operators")
{
  TEST_CASE("operator<_expected_true")
  {
    ft::vector<int> my_vector;
    ft::vector<int> my_vector2;

    my_vector.push_back(10);
    my_vector.push_back(11);
    my_vector.push_back(12);
    my_vector.push_back(13);
    my_vector.push_back(14);
    my_vector.push_back(15);
    my_vector.push_back(16);
    my_vector.push_back(17);

    my_vector2.push_back(18);
    my_vector2.push_back(19);
    my_vector2.push_back(20);
    my_vector2.push_back(21);
    my_vector2.push_back(22);
    my_vector2.push_back(23);
    my_vector2.push_back(24);
    my_vector2.push_back(25);

    CHECK(my_vector < my_vector2);
  }

  TEST_CASE("operator<_expected_false")
  {
    ft::vector<int> my_vector;
    ft::vector<int> my_vector2;

    my_vector.push_back(10);
    my_vector.push_back(11);
    my_vector.push_back(12);
    my_vector.push_back(26);
    my_vector.push_back(14);
    my_vector.push_back(15);
    my_vector.push_back(16);
    my_vector.push_back(17);

    my_vector2.push_back(18);
    my_vector2.push_back(19);
    my_vector2.push_back(20);
    my_vector2.push_back(21);
    my_vector2.push_back(22);
    my_vector2.push_back(23);
    my_vector2.push_back(24);
    my_vector2.push_back(25);

    CHECK_FALSE(my_vector > my_vector2);
  }

  TEST_CASE("operator>_expected_false")
  {
    ft::vector<int> my_vector;
    ft::vector<int> my_vector2;

    my_vector.push_back(10);
    my_vector.push_back(11);
    my_vector.push_back(12);
    my_vector.push_back(26);
    my_vector.push_back(14);
    my_vector.push_back(15);
    my_vector.push_back(16);
    my_vector.push_back(17);

    my_vector2.push_back(18);
    my_vector2.push_back(19);
    my_vector2.push_back(20);
    my_vector2.push_back(21);
    my_vector2.push_back(22);
    my_vector2.push_back(23);
    my_vector2.push_back(24);
    my_vector2.push_back(25);

    CHECK_FALSE(my_vector > my_vector2);
  }

  TEST_CASE("operator>_expected_true")
  {
    ft::vector<std::string> my_vector;
    ft::vector<std::string> my_vector2;

    my_vector.push_back("10");
    my_vector.push_back("11");
    my_vector.push_back("12");
    my_vector.push_back("13");
    my_vector.push_back("14");
    my_vector.push_back("15");
    my_vector.push_back("16");
    my_vector.push_back("17");

    my_vector2.push_back("18");
    my_vector2.push_back("19");
    my_vector2.push_back("20");
    my_vector2.push_back("21");
    my_vector2.push_back("22");
    my_vector2.push_back("23");
    my_vector2.push_back("24");
    my_vector2.push_back("25");

    CHECK(my_vector2 > my_vector);
  }

  TEST_CASE("operator==expected_true")
  {
    ft::vector<std::string> my_vector;
    ft::vector<std::string> my_vector2;

    my_vector.push_back("10");
    my_vector.push_back("10");
    my_vector.push_back("10");
    my_vector.push_back("10");
    my_vector.push_back("10");
    my_vector.push_back("10");

    my_vector2.push_back("10");
    my_vector2.push_back("10");
    my_vector2.push_back("10");
    my_vector2.push_back("10");
    my_vector2.push_back("10");
    my_vector2.push_back("10");

    CHECK(my_vector2 == my_vector);
  }

  TEST_CASE("operator!=expected_false")
  {
    ft::vector<int> my_vector;
    ft::vector<int> my_vector2;

    my_vector.push_back(10);
    my_vector.push_back(10);
    my_vector.push_back(10);
    my_vector.push_back(10);
    my_vector.push_back(10);
    my_vector.push_back(10);

    my_vector2.push_back(10);
    my_vector2.push_back(10);
    my_vector2.push_back(10);
    my_vector2.push_back(10);
    my_vector2.push_back(10);
    my_vector2.push_back(10);

    CHECK_FALSE(my_vector2 != my_vector);
  }

  TEST_CASE("operator<=_expected_true")
  {
    ft::vector<std::string> my_vector;
    ft::vector<std::string> my_vector2;

    my_vector.push_back("10");
    my_vector.push_back("11");
    my_vector.push_back("12");
    my_vector.push_back("13");
    my_vector.push_back("14");
    my_vector.push_back("15");
    my_vector.push_back("16");
    my_vector.push_back("17");

    my_vector2.push_back("18");
    my_vector2.push_back("19");
    my_vector2.push_back("20");
    my_vector2.push_back("21");
    my_vector2.push_back("22");
    my_vector2.push_back("23");
    my_vector2.push_back("24");
    my_vector2.push_back("25");

    CHECK(my_vector <= my_vector2);
  }
}
