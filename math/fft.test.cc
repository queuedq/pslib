#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "fft.cc"

TEST_CASE("Polynomial multiplication works") {
  vector<lld> P = {1, 4, 2};
  vector<lld> Q = {2, 3, 5};
  vector<lld> R = {1, 1, 1, 1};
  vector<lld> S = {100001, 100001, 100001, 100001};

  REQUIRE(conv(P, Q) == vector<lld>({2, 11, 21, 26, 10, 0, 0, 0}));
  REQUIRE(conv(R, R) == vector<lld>({1, 2, 3, 4, 3, 2, 1, 0}));

  REQUIRE(conv_2in1(P, Q) == vector<lld>({2, 11, 21, 26, 10, 0, 0, 0}));
  REQUIRE(conv_2in1(R, R) == vector<lld>({1, 2, 3, 4, 3, 2, 1, 0}));

  REQUIRE(conv_mod(S, S, 1e9) == vector<lld>({
    200001, 400002, 600003, 800004, 600003, 400002, 200001, 0
  }));
}
