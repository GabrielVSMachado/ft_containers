#include "doctest.h"
#include "RBTree.hpp"
#include "utility.hpp"
#include <string>
#include <vector>

template<typename T>
struct getFirst
{
  typename T::first_type const &operator()(T const &__value) const { return __value.first; }
};

typedef internals::RBTree<int, ft::pair<int, int>, getFirst<ft::pair<int, int> > > myRBT;

TEST_SUITE("iterator")
{
  TEST_CASE("begin_eq_the_lower_key_in_the_tree")
  {
    myRBT my_rbt;

    my_rbt.insert(ft::make_pair(1, 4));
    my_rbt.insert(ft::make_pair(2, 3));
    my_rbt.insert(ft::make_pair(3, 6));
    my_rbt.insert(ft::make_pair(4, 1));
    CHECK_EQ(my_rbt.begin()->second, 4);
  }

  TEST_CASE("expected_value_eq_the_third_element")
  {
    myRBT my_rbt;
    myRBT::iterator result;

    my_rbt.insert(ft::make_pair(1, 4));
    my_rbt.insert(ft::make_pair(2, 3));
    my_rbt.insert(ft::make_pair(3, 6));
    my_rbt.insert(ft::make_pair(4, 1));
    result = my_rbt.begin();
    ++result;
    ++result;
    CHECK_EQ(result->second, 6);
  }

  TEST_CASE("expected_value_eq_to_3_after_delete_the_key_4")
  {
    myRBT my_rbt;
    myRBT::iterator result;

    my_rbt.insert(ft::make_pair(4, 4));
    my_rbt.insert(ft::make_pair(3, 3));
    my_rbt.insert(ft::make_pair(7, 7));
    my_rbt.insert(ft::make_pair(6, 6));
    my_rbt.insert(ft::make_pair(1, 1));
    result = my_rbt.begin();
    ++result;
    ++result;
    ++result;
    my_rbt.erase(4);
    --result;
    CHECK_EQ(result->second, 3);
  }
}

TEST_SUITE("insert_value_type_as_only_parameter")
{
  TEST_CASE("expected_the_right_sequence_of_keys")
  {
    myRBT my_rbt;
    std::vector<int> expected;
    std::vector<int> result;

    expected.push_back(32);
    expected.push_back(21);
    expected.push_back(11);
    expected.push_back(1097);

    my_rbt.insert(ft::make_pair(3, 11));
    my_rbt.insert(ft::make_pair(2, 21));
    my_rbt.insert(ft::make_pair(1, 32));
    my_rbt.insert(ft::make_pair(4, 1097));

    myRBT::iterator i = my_rbt.begin();

    result.push_back(i->second);
    result.push_back((++i)->second);
    result.push_back((++i)->second);
    result.push_back((++i)->second);
    CHECK(result == expected);
  }
}
