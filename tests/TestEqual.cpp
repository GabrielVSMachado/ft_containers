#include "doctest.h"

#include "algorithms.hpp"
#include "vector.hpp"
#include <vector>

TEST_SUITE("equal")
{

  TEST_CASE("expected_false")
  {
    ft::vector<int> my_vector;
    std::vector<int> original(20, -32);
    ft::vector<int>::const_iterator result;

    my_vector.push_back(-32);
    my_vector.push_back(-32);
    my_vector.push_back(-32);
    my_vector.push_back(-32);
    my_vector.push_back(-32);
    my_vector.push_back(-32);
    my_vector.push_back(42);

    result = my_vector.begin();

    CHECK_FALSE(ft::equal(original.begin(), original.end(), result));
  }

  TEST_CASE("expected_true")
  {
    ft::vector<int> my_vector;
    std::vector<int> original(20, 10);
    ft::vector<int>::reverse_iterator result;

    for (int i = 0; i < 20; i++) {
      my_vector.push_back(10);
    }

    result = my_vector.rbegin();

    CHECK(ft::equal(original.rbegin(), original.rend(), result) == true);
  }

} // end of test suite equal
