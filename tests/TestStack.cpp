#include "doctest.h"
#include "stack.hpp"
#include <string>


TEST_SUITE("push")
{
  TEST_CASE("expected_no_error")
  {
    ft::stack<int> __s;

    __s.push(42);
    CHECK(true);
  }
}

TEST_SUITE("empty")
{
  TEST_CASE("exepcted_stack_empty")
  {
    ft::stack<int> __s;

    CHECK(__s.empty());
  }

  TEST_CASE("exepcted_stack_not_empty")
  {
    ft::stack<std::string> __s;

    __s.push("42sp");
    CHECK_FALSE(__s.empty());
  }
}

TEST_SUITE("size")
{
  TEST_CASE("expected_size_eq_0")
  {
    ft::stack<std::string> __s;

    CHECK_EQ(__s.size(), 0);
  }

  TEST_CASE("expected_size_gt_0")
  {
    ft::stack<std::string> __s;

    __s.push("42sp");
    __s.push("42sp");
    CHECK_GT(__s.size(), 0);
  }
}

TEST_SUITE("top")
{
  TEST_CASE("expected_top_eq_42")
  {
    ft::stack<int> __s;

    __s.push(42);
    CHECK_EQ(__s.top(), 42);
  }

  TEST_CASE("expected_top_eq_43")
  {
    ft::stack<std::string> __s;

    __s.push("42");
    __s.push("43");
    CHECK_EQ(__s.top(), "43");
  }

  TEST_CASE("const_top_overloading")
  {
    ft::vector<int> const __v(5, 10);
    ft::stack<int> const __s(__v);

    CHECK_EQ(__s.top(), 10);
  }
}

TEST_SUITE("pop")
{
  TEST_CASE("expected_size_eq_1")
  {
    ft::stack<float> __s;

    __s.push(3.14);
    __s.push(3.123423423524);
    __s.pop();
    CHECK_EQ(__s.size(), 1);
  }
}

TEST_SUITE("operator==")
{
  TEST_CASE("expected_true")
  {
    ft::stack<std::string> __s;
    ft::stack<std::string> __s2;

    __s.push("42");
    __s.push("43");
    __s.push("44");
    __s.push("45");
    __s.push("46");
    __s.push("47");


    __s2.push("42");
    __s2.push("43");
    __s2.push("44");
    __s2.push("45");
    __s2.push("46");
    __s2.push("47");
    CHECK(__s == __s2);
  }

  TEST_CASE("expected_false")
  {
    ft::stack<std::string> __s;
    ft::stack<std::string> __s2;

    __s.push("42");
    __s.push("43");
    __s.push("44");
    __s.push("45");
    __s.push("46");
    __s.push("47");


    __s2.push("42");
    __s2.push("43");
    __s2.push("44");
    __s2.push("45");
    __s2.push("46");
    __s2.push("61");

    CHECK_FALSE(__s == __s2);
  }
}

TEST_SUITE("operator<")
{
  TEST_CASE("expected_true")
  {
    ft::stack<int> __s;
    ft::stack<int> __s2;

    __s.push(42);
    __s.push(43);
    __s.push(44);
    __s.push(45);
    __s.push(46);
    __s.push(47);

    __s2.push(42);
    __s2.push(43);
    __s2.push(44);
    __s2.push(45);
    __s2.push(46);
    __s2.push(48);
    CHECK(__s < __s2);
  }

  TEST_CASE("expected_false")
  {
    ft::stack<int> __s;
    ft::stack<int> __s2;

    __s.push(42);
    __s.push(43);
    __s.push(44);
    __s.push(45);
    __s.push(46);
    __s.push(47);

    __s2.push(42);
    __s2.push(43);
    __s2.push(44);
    __s2.push(45);
    __s2.push(46);
    __s2.push(41);
    CHECK_FALSE(__s < __s2);
  }
}

TEST_SUITE("doesnt_have_iterator")
{
  TEST_CASE("loop_without_iterator_expected_vector_size_eq_stack_size_before_loop")
  {
    ft::stack<int> __s;
    ft::vector<int> __v(6);

    __s.push(42);
    __s.push(43);
    __s.push(44);
    __s.push(45);
    __s.push(46);
    __s.push(47);

    for (size_t i = 0; i < __s.size(); i++) {
      __v.insert(__v.begin(), __s.top());
      __s.pop();
    }

    ft::vector<int>::size_type const result = __v.size();
    CHECK_GT(result, __s.size());
  }
}
