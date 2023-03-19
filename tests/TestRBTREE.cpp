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

typedef internals::RBTree<int const, ft::pair<int const, std::string>, getFirst<ft::pair<int const, std::string> > > myISRBT;

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

TEST_SUITE("erase_range_iterator")
{
  TEST_CASE("expected_on_two_elements_left")
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
    my_rbt.erase(pos, my_rbt.end());
    CHECK(my_rbt.size() == 3);
  }

  TEST_CASE("expected_non_element_left")
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
    my_rbt.erase(my_rbt.begin(), my_rbt.end());
    CHECK(my_rbt.empty());
  }
}

TEST_SUITE("find")
{
  TEST_CASE("check_if_element_exist")
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
    mySRBT::iterator result = my_rbt.find("60");
    CHECK_EQ(result->second, 45);
  }
}

TEST_SUITE("lower_bound")
{
  TEST_CASE("expected_the_next_key")
  {
    myRBT my_rbt;
    std::vector<ft::pair<int const, int> > __v;

    __v.push_back(ft::make_pair(4, 43));
    // __v.push_back(ft::make_pair(2, 1));
    __v.push_back(ft::make_pair(1, 2));
    __v.push_back(ft::make_pair(3, 51));
    __v.push_back(ft::make_pair(5, 44));
    __v.push_back(ft::make_pair(6, 45));
    __v.push_back(ft::make_pair(7, 47));

    my_rbt.insert(__v.begin(), __v.end());
    myRBT::iterator result = my_rbt.lower_bound(2);
    CHECK_EQ(result->second, 51);
  }

  TEST_CASE("expected_the_same_key")
  {
    myRBT my_rbt;
    std::vector<ft::pair<int const, int> > __v;

    __v.push_back(ft::make_pair(4, 43));
    __v.push_back(ft::make_pair(2, 1));
    __v.push_back(ft::make_pair(1, 2));
    __v.push_back(ft::make_pair(3, 51));
    __v.push_back(ft::make_pair(5, 44));
    __v.push_back(ft::make_pair(6, 45));
    __v.push_back(ft::make_pair(7, 47));

    my_rbt.insert(__v.begin(), __v.end());
    myRBT::iterator result = my_rbt.lower_bound(1);
    CHECK_EQ(result->second, 2);
  }

  TEST_CASE("expected_end")
  {
    myRBT my_rbt;
    std::vector<ft::pair<int const, int> > __v;

    __v.push_back(ft::make_pair(4, 43));
    __v.push_back(ft::make_pair(2, 1));
    __v.push_back(ft::make_pair(1, 2));
    __v.push_back(ft::make_pair(3, 51));
    __v.push_back(ft::make_pair(5, 44));
    __v.push_back(ft::make_pair(6, 45));
    __v.push_back(ft::make_pair(7, 47));

    my_rbt.insert(__v.begin(), __v.end());
    myRBT::iterator result = my_rbt.lower_bound(8);
    CHECK_EQ(result, my_rbt.end());
  }
}

TEST_SUITE("upper_bound")
{
  TEST_CASE("expected_the_next_key")
  {
    myRBT my_rbt;
    std::vector<ft::pair<int const, int> > __v;

    __v.push_back(ft::make_pair(4, 43));
    __v.push_back(ft::make_pair(2, 1));
    __v.push_back(ft::make_pair(1, 2));
    __v.push_back(ft::make_pair(3, 51));
    __v.push_back(ft::make_pair(5, 44));
    __v.push_back(ft::make_pair(6, 45));
    __v.push_back(ft::make_pair(7, 47));

    my_rbt.insert(__v.begin(), __v.end());
    myRBT::iterator result = my_rbt.upper_bound(2);
    CHECK_EQ(result->second, 51);
  }

  TEST_CASE("expected_end")
  {
    myRBT my_rbt;
    std::vector<ft::pair<int const, int> > __v;

    __v.push_back(ft::make_pair(4, 43));
    __v.push_back(ft::make_pair(2, 1));
    __v.push_back(ft::make_pair(1, 2));
    __v.push_back(ft::make_pair(3, 51));
    __v.push_back(ft::make_pair(5, 44));
    __v.push_back(ft::make_pair(6, 45));
    __v.push_back(ft::make_pair(7, 47));

    my_rbt.insert(__v.begin(), __v.end());
    myRBT::iterator result = my_rbt.upper_bound(8);
    CHECK_EQ(result, my_rbt.end());
  }
}

TEST_SUITE("count")
{
  TEST_CASE("expected_0")
  {
    myRBT my_rbt;
    std::vector<ft::pair<int const, int> > __v;

    __v.push_back(ft::make_pair(4, 43));
    __v.push_back(ft::make_pair(2, 1));
    __v.push_back(ft::make_pair(1, 2));
    __v.push_back(ft::make_pair(3, 51));
    __v.push_back(ft::make_pair(5, 44));
    __v.push_back(ft::make_pair(6, 45));
    __v.push_back(ft::make_pair(7, 47));

    my_rbt.insert(__v.begin(), __v.end());
    CHECK_EQ(my_rbt.count(100), 0);
  }

  TEST_CASE("expected_1")
  {
    myRBT my_rbt;
    std::vector<ft::pair<int const, int> > __v;

    __v.push_back(ft::make_pair(4, 43));
    __v.push_back(ft::make_pair(2, 1));
    __v.push_back(ft::make_pair(1, 2));
    __v.push_back(ft::make_pair(3, 51));
    __v.push_back(ft::make_pair(5, 44));
    __v.push_back(ft::make_pair(6, 45));
    __v.push_back(ft::make_pair(7, 47));

    my_rbt.insert(__v.begin(), __v.end());
    CHECK_EQ(my_rbt.count(5), 1);
  }
}

TEST_SUITE("equal_range")
{
  TEST_CASE("expected_element_of_key_and_the_next")
  {
    myRBT my_rbt;
    std::vector<ft::pair<int const, int> > __v;

    __v.push_back(ft::make_pair(4, 43));
    __v.push_back(ft::make_pair(2, 1));
    __v.push_back(ft::make_pair(1, 2));
    __v.push_back(ft::make_pair(3, 51));
    __v.push_back(ft::make_pair(5, 44));
    __v.push_back(ft::make_pair(6, 45));
    __v.push_back(ft::make_pair(7, 47));

    my_rbt.insert(__v.begin(), __v.end());
    myRBT::iterator second = my_rbt.begin();
    ++second;
    myRBT::iterator first = second++;
    ft::pair<myRBT::iterator, myRBT::iterator> result = my_rbt.equal_range(2);
    CHECK_EQ(result, ft::make_pair(first, second));
  }

  TEST_CASE("expected_end")
  {
    myRBT my_rbt;
    std::vector<ft::pair<int const, int> > __v;

    __v.push_back(ft::make_pair(4, 43));
    __v.push_back(ft::make_pair(2, 1));
    __v.push_back(ft::make_pair(1, 2));
    __v.push_back(ft::make_pair(3, 51));
    __v.push_back(ft::make_pair(5, 44));
    __v.push_back(ft::make_pair(6, 45));
    __v.push_back(ft::make_pair(7, 47));

    my_rbt.insert(__v.begin(), __v.end());
    ft::pair<myRBT::iterator, myRBT::iterator> result = my_rbt.equal_range(8);
    CHECK_EQ(result, ft::make_pair(my_rbt.end(), my_rbt.end()));
  }

  TEST_CASE("expected_the_key_and_next_beound")
  {
    myRBT my_rbt;
    std::vector<ft::pair<int const, int> > __v;

    __v.push_back(ft::make_pair(4, 43));
    __v.push_back(ft::make_pair(1, 2));
    __v.push_back(ft::make_pair(5, 44));
    __v.push_back(ft::make_pair(6, 45));
    __v.push_back(ft::make_pair(7, 47));

    my_rbt.insert(__v.begin(), __v.end());
    myRBT::iterator first = my_rbt.begin();
    myRBT::iterator second = my_rbt.find(4);
    ft::pair<myRBT::iterator, myRBT::iterator> result = my_rbt.equal_range(1);
    CHECK_EQ(result, ft::make_pair(first, second));
  }
}

TEST_SUITE("booleans_operators")
{
  TEST_CASE("operator==_expected_true")
  {
    myRBT my_rbt;
    myRBT my_rbt2;
    std::vector<ft::pair<int const, int> > __v;

    __v.push_back(ft::make_pair(4, 43));
    __v.push_back(ft::make_pair(1, 2));
    __v.push_back(ft::make_pair(5, 44));
    __v.push_back(ft::make_pair(6, 45));
    __v.push_back(ft::make_pair(7, 47));

    my_rbt.insert(__v.begin(), __v.end());
    my_rbt2.insert(__v.begin(), __v.end());
    CHECK(my_rbt == my_rbt2);
  }

  TEST_CASE("operator==_expected_false_by_size")
  {
    myRBT my_rbt;
    myRBT my_rbt2;
    std::vector<ft::pair<int const, int> > __v;

    __v.push_back(ft::make_pair(4, 43));
    __v.push_back(ft::make_pair(1, 2));
    __v.push_back(ft::make_pair(5, 44));
    __v.push_back(ft::make_pair(6, 45));
    __v.push_back(ft::make_pair(7, 47));

    my_rbt.insert(__v.begin(), --__v.end());
    my_rbt2.insert(__v.begin(), __v.end());
    CHECK_FALSE(my_rbt == my_rbt2);
  }

  TEST_CASE("operator==_expected_false_by_values")
  {
    myRBT my_rbt;
    myRBT my_rbt2;
    std::vector<ft::pair<int const, int> > __v;

    __v.push_back(ft::make_pair(4, 43));
    __v.push_back(ft::make_pair(1, 2));
    __v.push_back(ft::make_pair(5, 44));
    __v.push_back(ft::make_pair(6, 45));
    __v.push_back(ft::make_pair(7, 47));

    my_rbt.insert(__v.begin(), --__v.end());
    my_rbt.insert(ft::make_pair(7, 55));
    my_rbt2.insert(__v.begin(), __v.end());
    CHECK_FALSE(my_rbt == my_rbt2);
  }

  TEST_CASE("operator<_expected_true")
  {
    myRBT my_rbt;
    myRBT my_rbt2;
    std::vector<ft::pair<int const, int> > __v;
    std::vector<ft::pair<int const, int> > __v2;

    __v2.push_back(ft::make_pair(4, 41));
    __v2.push_back(ft::make_pair(1, 42));
    __v2.push_back(ft::make_pair(5, 43));
    __v2.push_back(ft::make_pair(6, 44));
    __v2.push_back(ft::make_pair(7, 46));

    __v.push_back(ft::make_pair(8, 43));
    __v.push_back(ft::make_pair(9, 42));
    __v.push_back(ft::make_pair(10, 44));
    __v.push_back(ft::make_pair(11, 45));
    __v.push_back(ft::make_pair(12, 47));

    my_rbt.insert(__v.begin(), __v.end());
    my_rbt2.insert(__v2.begin(), __v2.end());
    CHECK(my_rbt2 < my_rbt);
  }

  TEST_CASE("operator<_expected_true_by_size")
  {
    myRBT my_rbt;
    myRBT my_rbt2;
    std::vector<ft::pair<int const, int> > __v;
    std::vector<ft::pair<int const, int> > __v2;

    __v2.push_back(ft::make_pair(4, 2));
    __v2.push_back(ft::make_pair(1, 1));
    __v2.push_back(ft::make_pair(5, 3));
    __v2.push_back(ft::make_pair(6, 4));

    __v.push_back(ft::make_pair(8, 43));
    __v.push_back(ft::make_pair(9, 42));
    __v.push_back(ft::make_pair(10, 44));
    __v.push_back(ft::make_pair(11, 45));
    __v.push_back(ft::make_pair(12, 47));

    my_rbt.insert(__v.begin(), __v.end());
    my_rbt2.insert(__v2.begin(), __v2.end());
    CHECK(my_rbt2 < my_rbt);
  }

  TEST_CASE("operator<_expected_false_by_values")
  {
    myISRBT my_rbt;
    myISRBT my_rbt2;
    std::vector<ft::pair<int const, std::string> > __v;
    std::vector<ft::pair<int const, std::string> > __v2;

    __v2.push_back(ft::make_pair(4, "41"));
    __v2.push_back(ft::make_pair(1, "42"));
    __v2.push_back(ft::make_pair(5, "43"));
    __v2.push_back(ft::make_pair(6, "44"));
    __v2.push_back(ft::make_pair(7, "47"));

    __v.push_back(ft::make_pair(8, "43"));
    __v.push_back(ft::make_pair(9, "42"));
    __v.push_back(ft::make_pair(10, "44"));
    __v.push_back(ft::make_pair(11, "45"));
    __v.push_back(ft::make_pair(12, "47"));

    my_rbt.insert(__v2.begin(), __v2.end());
    my_rbt2.insert(__v.begin(), __v.end());
    CHECK_FALSE(my_rbt2 < my_rbt);
  }
}

TEST_SUITE("assign_operator")
{
  TEST_CASE("expected_the_same_size")
  {
    mySRBT my_rbt;
    mySRBT my_rbt2;

    my_rbt2.insert(ft::make_pair("1", 1));
    my_rbt2.insert(ft::make_pair("3", 3));
    my_rbt2.insert(ft::make_pair("5", 5));
    my_rbt2.insert(ft::make_pair("6", 6));

    my_rbt = my_rbt2;
    CHECK_EQ(my_rbt.size(), my_rbt2.size());
  }

  TEST_CASE("expected_the_same_values")
  {
    mySRBT my_rbt;
    mySRBT my_rbt2;

    my_rbt2.insert(ft::make_pair("1", 1));
    my_rbt2.insert(ft::make_pair("3", 3));
    my_rbt2.insert(ft::make_pair("5", 5));
    my_rbt2.insert(ft::make_pair("6", 6));

    my_rbt = my_rbt2;
    CHECK(my_rbt == my_rbt2);
  }

  TEST_CASE("expected_deep_copy")
  {
    mySRBT my_rbt;
    mySRBT my_rbt2;

    my_rbt2.insert(ft::make_pair("1", 1));
    my_rbt2.insert(ft::make_pair("3", 3));
    my_rbt2.insert(ft::make_pair("5", 5));
    my_rbt2.insert(ft::make_pair("6", 6));

    my_rbt = my_rbt2;
    my_rbt.begin()->second = 42;
    CHECK_EQ(my_rbt2.begin()->second, 1);
  }
}

TEST_SUITE("swap")
{
  TEST_CASE("when_both_are_empty")
  {
    myRBT first;
    myRBT second;

    first.swap(second);
    CHECK(ft::make_pair(first.empty(), second.empty()) == ft::make_pair(true, true));
  }

  TEST_CASE("when_only_the_first_is_empty")
  {
    mySRBT first;
    mySRBT second;

    second.insert(ft::make_pair("1", 2));
    second.insert(ft::make_pair("2", 3));
    second.insert(ft::make_pair("3", 4));
    second.insert(ft::make_pair("4", 5));

    first.swap(second);
    ft::pair<myRBT::size_type, bool> result(first.size(), second.empty());
    CHECK(ft::make_pair(4lu, true) == result);
  }

  TEST_CASE("when_both_have_elements_expected_no_key_3_in_second")
  {
    mySRBT first;
    mySRBT second;

    second.insert(ft::make_pair("1", 2));
    second.insert(ft::make_pair("2", 3));
    second.insert(ft::make_pair("3", 4));
    second.insert(ft::make_pair("4", 5));

    first.insert(ft::make_pair("1", 2));
    first.insert(ft::make_pair("2", 3));
    first.insert(ft::make_pair("4", 5));

    first.swap(second);
    CHECK(second.find("3") == second.end());
  }

  TEST_CASE("when_both_have_elements_expected_first_size_eq_4")
  {
    mySRBT first;
    mySRBT second;

    second.insert(ft::make_pair("1", 2));
    second.insert(ft::make_pair("2", 3));
    second.insert(ft::make_pair("3", 4));
    second.insert(ft::make_pair("4", 5));

    first.insert(ft::make_pair("1", 2));
    first.insert(ft::make_pair("2", 3));
    first.insert(ft::make_pair("4", 5));

    first.swap(second);
    CHECK(first.size() == 4lu);
  }
}
