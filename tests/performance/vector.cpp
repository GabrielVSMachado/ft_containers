#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

TEST_SUITE("insert_performance")
{
  TEST_CASE("insert_1000000_with_integral_constant")
  {
    // INFO("insert_1000000_with_integral_constant");
    ft::vector<unsigned int> my_vector;

    for (unsigned int i = 0; i != 1000000; i++) {
      my_vector.insert(my_vector.end(), i);
    }
    MESSAGE("ola");
  }
}

