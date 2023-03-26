#include "doctest.h"
#include "map.hpp"
#include "utility.hpp"
#include <string>
#include <vector>


TEST_SUITE("constructor_range_iterator")
{
  TEST_CASE("expected_all_elements_in_a_const_map")
  {
    std::vector<ft::pair<int, int> > __v;

    __v.push_back(ft::make_pair(1, 1));
    __v.push_back(ft::make_pair(2, 2));
    __v.push_back(ft::make_pair(3, 3));
    __v.push_back(ft::make_pair(4, 4));
    __v.push_back(ft::make_pair(5, 5));

    ft::map<int, int> const myMap(__v.begin(), __v.end());
    CHECK(myMap.size() == 5);
  }

  TEST_CASE("expected_exception")
  {
    std::vector<ft::pair<int, int> > __v;

    __v.push_back(ft::make_pair(1, 1));
    __v.push_back(ft::make_pair(2, 2));
    __v.push_back(ft::make_pair(3, 3));
    __v.push_back(ft::make_pair(4, 4));
    __v.push_back(ft::make_pair(5, 5));

    ft::map<int, int> const myMap(__v.begin(), __v.end());
    CHECK(myMap.size() == 5);
  }
}

TEST_SUITE("value_compare")
{
  TEST_CASE("value_comp_expected_true")
  {
    std::vector<ft::pair<int, int> > __v;

    __v.push_back(ft::make_pair(1, 1));
    __v.push_back(ft::make_pair(2, 2));
    __v.push_back(ft::make_pair(3, 3));
    __v.push_back(ft::make_pair(4, 4));
    __v.push_back(ft::make_pair(5, 5));

    ft::map<int, int> const myMap(__v.begin(), __v.end());
    ft::map<int, int>::value_compare  result = myMap.value_comp();
    CHECK(result(*myMap.begin(), *(++myMap.begin())));
  }

  TEST_CASE("value_comp_expected_false")
  {
    std::vector<ft::pair<int, int> > __v;

    __v.push_back(ft::make_pair(1, 1));
    __v.push_back(ft::make_pair(2, 2));
    __v.push_back(ft::make_pair(3, 3));
    __v.push_back(ft::make_pair(4, 4));
    __v.push_back(ft::make_pair(5, 5));

    ft::map<int, int> const myMap(__v.begin(), __v.end());
    ft::map<int, int>::value_compare  result = myMap.value_comp();
    CHECK_FALSE(result(*(++myMap.begin()), *myMap.begin()));
  }
}

TEST_SUITE("operator==")
{
  TEST_CASE("expected_true")
  {
    ft::map<std::string, int> __m;

    __m.insert(ft::make_pair("42", 42));
    __m.insert(ft::make_pair("43", 43));
    __m.insert(ft::make_pair("44", 44));
    __m.insert(ft::make_pair("45", 45));
    __m.insert(ft::make_pair("46", 46));
    __m.insert(ft::make_pair("47", 47));

    ft::map<std::string, int> __m2(__m);

    CHECK(__m2 == __m);
  }

  TEST_CASE("expected_false")
  {
    ft::map<std::string, int> __m;

    __m.insert(ft::make_pair("42", 42));
    __m.insert(ft::make_pair("43", 43));
    __m.insert(ft::make_pair("44", 44));
    __m.insert(ft::make_pair("45", 45));
    __m.insert(ft::make_pair("46", 46));
    __m.insert(ft::make_pair("47", 47));

    ft::map<std::string, int> __m2(__m);

    __m2.rbegin()->second = 48;

    CHECK_FALSE(__m2 == __m);
  }
}

TEST_SUITE("operator<")
{
  TEST_CASE("expected_true")
  {
    ft::map<std::string, int> __m;

    __m.insert(ft::make_pair("42", 42));
    __m.insert(ft::make_pair("43", 43));
    __m.insert(ft::make_pair("44", 44));
    __m.insert(ft::make_pair("45", 45));
    __m.insert(ft::make_pair("46", 46));
    __m.insert(ft::make_pair("47", 47));

    ft::map<std::string, int> __m2(__m);

    __m2.rbegin()->second = 48;

    CHECK(__m < __m2);
  }

  TEST_CASE("expected_false")
  {
    ft::map<std::string, int> __m;

    __m.insert(ft::make_pair("42", 42));
    __m.insert(ft::make_pair("43", 43));
    __m.insert(ft::make_pair("44", 44));
    __m.insert(ft::make_pair("45", 45));
    __m.insert(ft::make_pair("46", 46));
    __m.insert(ft::make_pair("47", 49));

    ft::map<std::string, int> __m2(__m);

    __m2.rbegin()->second = 48;

    CHECK_FALSE(__m < __m2);
  }
}
