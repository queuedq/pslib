#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "fft.cc"

TEST_CASE("Polynomial multiplication works") {
  vector<lld> P = {1, 4, 2};
  vector<lld> Q = {2, 3, 5};
  vector<lld> R = {1, 1, 1, 1};

  REQUIRE(multiply(P, Q) == vector<lld>({2, 11, 21, 26, 10, 0, 0, 0}));
  REQUIRE(multiply(R, R) == vector<lld>({1, 2, 3, 4, 3, 2, 1, 0}));
}
