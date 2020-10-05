#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "dsu.cc"

TEST_CASE("DSU works") {
  const int size = 25;
  disjoint_set D(size);

  for (int i=0; i<20; i++) D.merge(i, i+5);

  REQUIRE(D.find(3) == D.find(23));
  REQUIRE(D.same(3, 23));
  REQUIRE(D.size(13) == 5);
}
