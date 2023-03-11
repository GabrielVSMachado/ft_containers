#include "doctest.h"
#include "RBTree.hpp"
#include "utility.hpp"
#include <vector>

TEST_SUITE("iterator")
{
  TEST_CASE("begin_eq_the_lower_key_in_the_tree")
  {
    internals::RBTree<int, int> myRBT;

    myRBT.insert(ft::make_pair(1, 4));
    myRBT.insert(ft::make_pair(2, 3));
    myRBT.insert(ft::make_pair(3, 6));
    myRBT.insert(ft::make_pair(4, 1));
    CHECK_EQ(myRBT.begin()->second, 4);
  }

  TEST_CASE("expected_value_eq_the_third_element")
  {
    internals::RBTree<int, int> myRBT;
    internals::RBTree<int, int>::iterator result;

    myRBT.insert(ft::make_pair(1, 4));
    myRBT.insert(ft::make_pair(2, 3));
    myRBT.insert(ft::make_pair(3, 6));
    myRBT.insert(ft::make_pair(4, 1));
    result = myRBT.begin();
    ++result;
    ++result;
    CHECK_EQ(result->second, 6);
  }

  TEST_CASE("expected_value_eq_to_3_after_delete_the_key_4")
  {
    internals::RBTree<int, int> myRBT;
    internals::RBTree<int, int>::iterator result;

    myRBT.insert(ft::make_pair(4, 4));
    myRBT.insert(ft::make_pair(3, 3));
    myRBT.insert(ft::make_pair(7, 7));
    myRBT.insert(ft::make_pair(6, 6));
    myRBT.insert(ft::make_pair(1, 1));
    result = myRBT.begin();
    ++result;
    ++result;
    ++result;
    myRBT.deleteKey(4);
    --result;
    CHECK_EQ(result->second, 3);
  }
}

TEST_SUITE("insert_value_type_as_only_parameter")
{
  TEST_CASE("expected_the_right_sequence_of_keys")
  {
    internals::RBTree<int, int> myRBT;
    std::vector<int> expected;
    std::vector<int> result;

    expected.push_back(32);
    expected.push_back(21);
    expected.push_back(11);
    expected.push_back(1097);

    myRBT.insert(ft::make_pair(3, 11));
    myRBT.insert(ft::make_pair(2, 21));
    myRBT.insert(ft::make_pair(1, 32));
    myRBT.insert(ft::make_pair(4, 1097));

    internals::RBTree<int, int>::iterator i = myRBT.begin();

    result.push_back(i->second);
    result.push_back((++i)->second);
    result.push_back((++i)->second);
    result.push_back((++i)->second);
    CHECK(result == expected);
  }
}
