#include "doctest.h"
#include "RBTree.hpp"
#include "utility.hpp"

TEST_SUITE("iterator")
{
  TEST_CASE("begin_eq_the_lower_value_in_the_tree")
  {
    internals::RBTree<int, int> myRBT;

    myRBT.insert(ft::make_pair(1, 4));
    myRBT.insert(ft::make_pair(2, 3));
    myRBT.insert(ft::make_pair(3, 6));
    myRBT.insert(ft::make_pair(4, 1));
    CHECK_EQ(myRBT.begin()->second, 1);
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
    ++result;
    CHECK_EQ(result->second, 6);
  }

  TEST_CASE("expected_value_eq_to_1_after_delete_the_key_4")
  {
    internals::RBTree<int, int> myRBT;
    internals::RBTree<int, int>::iterator result;

    myRBT.insert(ft::make_pair(1, 4));
    myRBT.insert(ft::make_pair(2, 3));
    myRBT.insert(ft::make_pair(3, 7));
    myRBT.insert(ft::make_pair(4, 6));
    myRBT.insert(ft::make_pair(5, 1));
    result = myRBT.begin();
    ++result;
    myRBT.deleteKey(1);
    --result;
    CHECK_EQ(result->second, 1);
  }
}

TEST_SUITE("reverse_iterator")
{
  TEST_CASE("rbegin_eq_the_maximun_value_in_the_tree")
  {
    internals::RBTree<int, int> myRBT;

    myRBT.insert(ft::make_pair(1, 4));
    myRBT.insert(ft::make_pair(2, 3));
    myRBT.insert(ft::make_pair(3, 6));
    myRBT.insert(ft::make_pair(4, 1));
    CHECK_EQ(myRBT.rbegin()->second, 6);
  }

  TEST_CASE("expected_the_lower_value_in_the_tree")
  {
    internals::RBTree<int, int> myRBT;
    internals::RBTree<int, int>::reverse_iterator result;

    myRBT.insert(ft::make_pair(1, 4));
    myRBT.insert(ft::make_pair(2, 3));
    myRBT.insert(ft::make_pair(3, 6));
    myRBT.insert(ft::make_pair(4, 1));
    result = myRBT.rbegin();
    ++result;
    ++result;
    ++result;
    CHECK_EQ(result->second, 1);

  }

  TEST_CASE("expected_value_eq_to_3")
  {
    internals::RBTree<int, int> myRBT;
    internals::RBTree<int, int>::reverse_iterator result;

    myRBT.insert(ft::make_pair(1, 4));
    myRBT.insert(ft::make_pair(2, 3));
    myRBT.insert(ft::make_pair(3, 6));
    myRBT.insert(ft::make_pair(4, 1));
    result = myRBT.rbegin();
    ++result;
    ++result;
    ++result;
    --result;
    CHECK_EQ(result->second, 3);
  }

  TEST_CASE("expected_value_eq_to_6_after_delete_another_key")
  {
    internals::RBTree<int, int> myRBT;
    internals::RBTree<int, int>::reverse_iterator result;

    myRBT.insert(ft::make_pair(1, 4));
    myRBT.insert(ft::make_pair(2, 7));
    myRBT.insert(ft::make_pair(3, 3));
    myRBT.insert(ft::make_pair(4, 6));
    myRBT.insert(ft::make_pair(5, 1));
    result = myRBT.rbegin();
    ++result;
    ++result;
    myRBT.deleteKey(1);
    --result;
    CHECK_EQ(result->second, 6);
  }
}

