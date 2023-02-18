#include "doctest.h"
#include "RBTree.hpp"

TEST_SUITE("insert")
{
  TEST_CASE("search_for_existents_elements")
  {
    internals::RBTree myRBT;
    bool result;

    myRBT.insert(4);
    myRBT.insert(5);
    myRBT.insert(3);
    myRBT.insert(1);
    result = myRBT.search(3) && myRBT.search(1) && myRBT.search(5) && myRBT.search(4);
    CHECK(result);
  }

  TEST_CASE("search_for_inexistent_element")
  {
    internals::RBTree myRBT;
    bool result;

    myRBT.insert(41);
    myRBT.insert(43);
    myRBT.insert(40);
    myRBT.insert(45);
    result = myRBT.search(42);
    CHECK_FALSE(result);
  }
}
