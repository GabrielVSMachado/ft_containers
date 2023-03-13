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

typedef internals::RBTree<int const, ft::pair<int const, int>, getFirst<ft::pair<int const, int> > > myRBT;

typedef internals::RBTree<std::string const, ft::pair<std::string const, int>, getFirst<ft::pair<std::string const, int> > > mySRBT;

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

TEST_SUITE("insert_only_one_parameter")
{
  TEST_CASE("expected_the_element_inserted")
  {
    mySRBT my_rbt;
    ft::pair<mySRBT::iterator, bool> result;

    result = my_rbt.insert(ft::make_pair("42", 42));
    CHECK_EQ(result.second, true);
  }

  TEST_CASE("expected_the_element_not_inserted")
  {
    mySRBT my_rbt;
    ft::pair<mySRBT::iterator, bool> result;

    my_rbt.insert(ft::make_pair("42", 42));
    result = my_rbt.insert(ft::make_pair("42", 43));
    CHECK_EQ(result.second, false);
  }

  TEST_CASE("expected_the_right_sequence_of_keys")
  {
    myRBT my_rbt;
    std::vector<int> expected;
    std::vector<int> result;

    expected.push_back(21);
    expected.push_back(11);
    expected.push_back(1097);

    my_rbt.insert(ft::make_pair(3, 11));
    my_rbt.insert(ft::make_pair(1, 21));
    my_rbt.insert(ft::make_pair(1, 32));
    my_rbt.insert(ft::make_pair(4, 1097));

    myRBT::iterator i = my_rbt.begin();

    result.push_back(i->second);
    result.push_back((++i)->second);
    result.push_back((++i)->second);
    CHECK(result == expected);
  }
}

TEST_SUITE("insert_hint_overloading")
{
  TEST_CASE("expected_insertion_in_the_indicated_position")
  {
    myRBT my_rbt;

    my_rbt.insert(ft::make_pair(1, 42));
    my_rbt.insert(ft::make_pair(3, 44));
    my_rbt.insert(ft::make_pair(4, 45));
    my_rbt.insert(ft::make_pair(5, 47));

    myRBT::iterator position = my_rbt.begin();
    ++position;
    myRBT::iterator result = my_rbt.insert(position, ft::make_pair(2, 43));
    CHECK_EQ(result->second, 43);
  }

  TEST_CASE("expected_not_insert_element")
  {
    myRBT my_rbt;

    my_rbt.insert(ft::make_pair(1, 42));
    my_rbt.insert(ft::make_pair(3, 44));
    my_rbt.insert(ft::make_pair(4, 45));
    my_rbt.insert(ft::make_pair(5, 47));

    myRBT::iterator position = my_rbt.begin();
    ++position;
    ++position;
    myRBT::iterator result = my_rbt.insert(position, ft::make_pair(3, 43));
    CHECK_EQ(result->second, 44);
  }
}

TEST_SUITE("insert_range_iterators")
{
  TEST_CASE("expected_begin_eq_2")
  {
    std::vector<ft::pair<int const, int> > __v;
    myRBT my_rbt;

    __v.push_back(ft::make_pair(4, 43));
    __v.push_back(ft::make_pair(2, 1));
    __v.push_back(ft::make_pair(1, 2));
    __v.push_back(ft::make_pair(3, 51));
    __v.push_back(ft::make_pair(5, 44));
    __v.push_back(ft::make_pair(6, 45));
    __v.push_back(ft::make_pair(7, 47));

    my_rbt.insert(__v.begin(), __v.end());
    CHECK_EQ(my_rbt.begin()->second, 2);
  }
}

TEST_SUITE("erase_iterator_overload")
{
  TEST_CASE("expected_element_deleted")
  {
    mySRBT my_rbt;
    std::vector<ft::pair<std::string const, int> > __v;

    __v.push_back(ft::make_pair("14", 43));
    __v.push_back(ft::make_pair("23", 1));
    __v.push_back(ft::make_pair("12", 2));
    __v.push_back(ft::make_pair("3", 51));
    __v.push_back(ft::make_pair("45", 44));
    __v.push_back(ft::make_pair("60", 45));
    __v.push_back(ft::make_pair("17", 47));

    my_rbt.insert(__v.begin(), __v.end());
    mySRBT::iterator pos = my_rbt.begin();
    ++pos;
    ++pos;
    ++pos;
    std::string const key = pos->first;
    my_rbt.erase(pos);
    CHECK(my_rbt.find(key) == my_rbt.end());
  }
}
