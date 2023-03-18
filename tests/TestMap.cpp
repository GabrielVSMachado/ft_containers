#include "doctest.h"
#include "map.hpp"
#include "utility.hpp"
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
