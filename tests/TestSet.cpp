#include "algorithms.hpp"
#include "doctest.h"
#include "set.hpp"
#include <string>
#include <vector>

TEST_SUITE("iterators")
{
  TEST_CASE("expected_element_eq_42")
  {
    ft::set<std::string> __s;

    __s.insert("43");
    __s.insert("44");
    __s.insert("45");
    __s.insert("46");
    __s.insert("42");

    ft::set<std::string>::iterator result = __s.find("42");
    CHECK_EQ(*result, "42");
  }

  TEST_CASE("expected_element_eq_43")
  {
    ft::set<std::string> __s;

    __s.insert("43");
    __s.insert("44");
    __s.insert("45");
    __s.insert("46");
    __s.insert("42");

    ft::set<std::string>::const_iterator result = __s.find("43");
    CHECK_EQ(*result, "43");
  }
}

TEST_SUITE("constructors")
{
  TEST_CASE("range_constructor")
  {
    std::vector<double> __v;

    __v.push_back(2.3435);
    __v.push_back(3.3435);
    __v.push_back(4.3538);
    __v.push_back(6.3465);
    __v.push_back(8.3435);

    ft::set<double> __s(__v.begin(), __v.end());
    CHECK(ft::equal(__v.begin(), __v.end(), __s.begin()));
  }

  TEST_CASE("copy")
  {
    ft::set<std::string> __s;

    __s.insert("42");
    __s.insert("43");
    __s.insert("44");
    __s.insert("45");
    __s.insert("46");

    ft::set<std::string> __s2(__s);
    CHECK(ft::equal(__s.begin(), __s.end(), __s2.begin()));
  }
}

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

TEST_SUITE("value_compare")
{
  TEST_CASE("value_comp_expected_true")
  {
    std::vector<int> __v;

    __v.push_back(1);
    __v.push_back(2);
    __v.push_back(3);
    __v.push_back(4);
    __v.push_back(5);

    ft::set<int> const mySet(__v.begin(), __v.end());
    ft::set<int>::value_compare  result = mySet.value_comp();
    CHECK(result(*mySet.begin(), *(++mySet.begin())));
  }

  TEST_CASE("value_comp_expected_false")
  {
    std::vector<int> __v;

    __v.push_back(1);
    __v.push_back(2);
    __v.push_back(3);
    __v.push_back(4);
    __v.push_back(5);

    ft::set<int> const mySet(__v.begin(), __v.end());
    ft::set<int>::value_compare  result = mySet.value_comp();
    CHECK_FALSE(result(*(++mySet.begin()), *mySet.begin()));
  }
}
