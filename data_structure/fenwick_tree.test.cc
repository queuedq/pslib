#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "fenwick_tree.cc"

TEST_CASE("Fenwick tree works") {
  // Array: {1..10, 0..0}
  fenwick_tree F(20);
  for (int i=1; i<=10; i++) F.add(i, i);

  REQUIRE(F.sum(0) == 0);
  REQUIRE(F.sum(5) == 15);
  REQUIRE(F.sum(10) == 55);
  REQUIRE(F.sum(20) == 55);
}
