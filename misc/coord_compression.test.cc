#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "coord_compression.cc"

TEST_CASE("Coordinate compression works") {
  vector<lld> xs = {-10, 12, 7, -4, 7, -4};
  compress(xs);

  REQUIRE(xs == vector<lld>({-10, -4, 7, 12}));

  REQUIRE(idx(-10, xs) == 0);
  REQUIRE(idx(-4, xs) == 1);
  REQUIRE(idx(7, xs) == 2);
  REQUIRE(idx(12, xs) == 3);
}
