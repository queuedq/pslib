#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "crt.cc"

TEST_CASE("CRT works") {
  REQUIRE(crt(3, 5, 7, 9) == pll(43, 45));
  REQUIRE(crt(4, 12, 10, 15) == pll(40, 60)); // gcd(12, 15) = 3
  REQUIRE(crt(1, 12, 2, 15) == pll(0, 0)); // 1 !== 2 (mod 3)
}
