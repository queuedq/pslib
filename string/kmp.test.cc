#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "kmp.cc"

TEST_CASE("KMP failure function is calculated") {
  REQUIRE(failure("aaaa") == vector({0, 1, 2, 3}));
  REQUIRE(failure("abaababaa") == vector({0, 0, 1, 1, 2, 3, 2, 3, 4}));
}

TEST_CASE("KMP finds all substrings") {
  REQUIRE(kmp("aaaa", "aa") == vector({0, 1, 2}));
  REQUIRE(kmp("abaababaa", "aba") == vector({0, 3, 5}));
  REQUIRE(kmp("aaaa", "b").empty());
}
