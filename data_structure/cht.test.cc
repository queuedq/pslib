#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "cht.cc"

TEST_CASE("CHT works") {
  CHT cht; // dec slope, min query
  cht.push(1, 0);
  cht.push(0, -2);
  cht.push(-1, 3); // will be popped
  cht.push(-2, 4);

  SECTION("Lines are stored correctly") {
    REQUIRE(sz(cht.dq) == 3);
    REQUIRE(cht.dq[0].a == 1); REQUIRE(cht.dq[0].l == -INFINITY); REQUIRE(cht.dq[0].r == -2);
    REQUIRE(cht.dq[1].a == 0); REQUIRE(cht.dq[1].l == -2); REQUIRE(cht.dq[1].r == 3);
    REQUIRE(cht.dq[2].a == -2); REQUIRE(cht.dq[2].l == 3); REQUIRE(cht.dq[2].r == INFINITY);
  }

  SECTION("Any query") {
    REQUIRE(cht.min(0) == -2);
    REQUIRE(cht.min(-3) == -3);
    REQUIRE(cht.min(4) == -4);
  }

  SECTION("Inc query") {
    REQUIRE(cht.min_pop(-3) == -3); REQUIRE(sz(cht.dq) == 3);
    REQUIRE(cht.min_pop(0) == -2); REQUIRE(sz(cht.dq) == 2);
    REQUIRE(cht.min_pop(4) == -4); REQUIRE(sz(cht.dq) == 1);
  }
}
