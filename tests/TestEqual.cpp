#include "doctest.h"

#include "algorithms.hpp"
#include "vector.hpp"
#include <string>
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

TEST_SUITE("lexicographical_compare")
{
  TEST_CASE("expected_false_equal_containers")
  {
    ft::vector<std::string> my_vector;
    std::vector<std::string> original;

    my_vector.push_back("1");
    my_vector.push_back("2");
    my_vector.push_back("3");
    my_vector.push_back("4");
    my_vector.push_back("5");
    my_vector.push_back("6");
    my_vector.push_back("7");
    my_vector.push_back("8");
    my_vector.push_back("9");
    my_vector.push_back("10");

    original.push_back("1");
    original.push_back("2");
    original.push_back("3");
    original.push_back("4");
    original.push_back("5");
    original.push_back("6");
    original.push_back("7");
    original.push_back("8");
    original.push_back("9");
    original.push_back("10");
    CHECK_FALSE(
      ft::lexicographical_compare(
        original.begin(), original.end(), my_vector.begin(), my_vector.end())
    );
  }
}
