#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "point.cc"

TEST_CASE("Point operations work") {
  // ^
  // |     R
  // |
  // | P
  // |       Q
  // + - - - - >
  Point<lld> P(1, 2), Q(4, 1), R(3, 4);

  SECTION("basic operators") {
    REQUIRE(P * 3 == Point<lld>(3, 6));
    REQUIRE(P * Q == 6);
  }

  SECTION("string representation") {
    ostringstream os; os << P;
    REQUIRE(os.str() == "(1, 2)");
  }

  SECTION("cross product stuff") {
    REQUIRE(cross(P, Q) == -7);

    REQUIRE(ccw(P, Q, R) > 0);
    REQUIRE(ccw(P, R, Q) < 0);
    REQUIRE(ccw<lld>({1, 1}, {2, 2}, {4, 4}) == 0);

    // TODO: Add area function
  }

  SECTION("length and angle") {
    REQUIRE(length(Point<lld>(1, 0)) == Approx(1));
    REQUIRE(length(P) == Approx(sqrt(5)));

    REQUIRE(angle<lld>({1, 0}, {1, 1}) == Approx(PI/4));
    REQUIRE(angle(P, Q) == Approx(2.4329663815));
    REQUIRE_THROWS_AS(angle<lld>({0, 0}, {1, 0}), invalid_argument);
  }
}
