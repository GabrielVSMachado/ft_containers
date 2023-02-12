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

    my_vector.push_back(-32);
    my_vector.push_back(-32);
    my_vector.push_back(-32);
    my_vector.push_back(-32);
    my_vector.push_back(-32);
    my_vector.push_back(-32);
    my_vector.push_back(42);

    CHECK_FALSE(ft::equal(original.begin(), original.end(), my_vector.begin()));
  }

  TEST_CASE("expected_true")
  {
    ft::vector<int> my_vector;
    std::vector<int> original(20, 10);

    for (int i = 0; i < 20; i++) {
      my_vector.push_back(10);
    }
    CHECK(ft::equal(original.rbegin(), original.rend(), my_vector.rbegin()));
  }

} // end of test suite equal
