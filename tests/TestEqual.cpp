#include "algorithms.hpp"
#include "criterion/assert.h"
#include "criterion/criterion.h"
#include "criterion/internal/assert.h"
#include "vector.hpp"
#include <criterion/criterion.h>
#include <vector>

Test(equal, expected_false)
{
  ft::vector<int> my_vector;
  std::vector<int> original(20, -32);
  typename ft::vector<int>::const_iterator result;

  my_vector.push_back(-32);
  my_vector.push_back(-32);
  my_vector.push_back(-32);
  my_vector.push_back(-32);
  my_vector.push_back(-32);
  my_vector.push_back(-32);
  my_vector.push_back(42);

  result = my_vector.begin();

  cr_assert(ft::equal(original.begin(), original.end(), result) == false);
}

Test(equal, expected_true)
{
  ft::vector<int> my_vector;
  std::vector<int> original(20, 10);
  typename ft::vector<int>::reverse_iterator result;

  for (int i = 0; i < 20; i++) {
    my_vector.push_back(10);
  }

  result = my_vector.rbegin();

  cr_assert(ft::equal(original.rbegin(), original.rend(), result) == true);
}
