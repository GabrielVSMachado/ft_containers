#include "doctest.h"
#include "set.hpp"
#include <string>

TEST_SUITE("operators_booleans_friend")
{
  TEST_CASE("operator==_expected_true")
  {
    ft::set<int> mySet;
    ft::set<int> mySet2;

    mySet2.insert(1);
    mySet2.insert(2);
    mySet2.insert(3);
    mySet2.insert(4);
    mySet2.insert(5);
    mySet2.insert(6);
    mySet2.insert(7);
    mySet2.insert(8);
    mySet2.insert(9);
    mySet2.insert(10);
    mySet2.insert(11);
    mySet2.insert(12);

    mySet.insert(1);
    mySet.insert(2);
    mySet.insert(3);
    mySet.insert(4);
    mySet.insert(5);
    mySet.insert(6);
    mySet.insert(7);
    mySet.insert(8);
    mySet.insert(9);
    mySet.insert(10);
    mySet.insert(11);
    mySet.insert(12);

    CHECK(mySet == mySet2);
  }

  TEST_CASE("operator==_expected_false")
  {
    ft::set<std::string> mySet;
    ft::set<std::string> mySet2;

    mySet.insert("1");
    mySet.insert("2");
    mySet.insert("3");
    mySet.insert("4");
    mySet.insert("5");
    mySet.insert("6");
    mySet.insert("7");
    mySet.insert("8");
    mySet.insert("9");
    mySet.insert("10");
    mySet.insert("11");
    mySet.insert("12");
    mySet.insert("13");

    mySet2.insert("1");
    mySet2.insert("2");
    mySet2.insert("20");
    mySet2.insert("4");
    mySet2.insert("5");
    mySet2.insert("6");
    mySet2.insert("7");
    mySet2.insert("8");
    mySet2.insert("9");
    mySet2.insert("10");
    mySet2.insert("11");
    mySet2.insert("12");
    mySet2.insert("13");

    CHECK_FALSE(mySet2 == mySet);
  }

  TEST_CASE("operator<_expected_true")
  {
    ft::set<std::string> mySet;
    ft::set<std::string> mySet2;

    mySet.insert("1");
    mySet.insert("2");
    mySet.insert("3");
    mySet.insert("4");
    mySet.insert("5");
    mySet.insert("6");
    mySet.insert("7");
    mySet.insert("8");
    mySet.insert("9");
    mySet.insert("10");
    mySet.insert("11");
    mySet.insert("12");
    mySet.insert("13");

    mySet2.insert("1");
    mySet2.insert("4");
    mySet2.insert("40");
    mySet2.insert("5");
    mySet2.insert("6");
    mySet2.insert("7");
    mySet2.insert("8");
    mySet2.insert("9");
    mySet2.insert("10");
    mySet2.insert("11");
    mySet2.insert("12");
    mySet2.insert("13");

    bool result = mySet < mySet2;
    CHECK(result);
  }
}
