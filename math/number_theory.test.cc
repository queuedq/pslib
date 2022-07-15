#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "number_theory.cc"

TEST_CASE("gcd, egcd works") {
  REQUIRE(gcd(21, 33) == 3);
  lld x, y;
  REQUIRE(egcd(21, 33, x, y) == 3);
  REQUIRE(x == -3);
  REQUIRE(y == 2);
}

TEST_CASE("modinv works") {
  REQUIRE(modinv(13, 7) == 6);
  REQUIRE(modinv(7, 13) == 2);
}

TEST_CASE("modpow works") {
  REQUIRE(modpow(3, 5, 17) == 5);
  REQUIRE(modpow(0, 5, 17) == 0);
  REQUIRE(modpow(3, 0, 17) == 1);
}

TEST_CASE("phi works") {
  REQUIRE(phi(504) == 144); // 2^3 * 3^2 * 7
}

TEST_CASE("CRT works") {
  REQUIRE(crt(3, 5, 7, 9) == pll(43, 45));
  REQUIRE(crt(4, 12, 10, 15) == pll(40, 60)); // gcd(12, 15) = 3
  REQUIRE(crt(1, 12, 2, 15) == pll(0, 0)); // 1 !== 2 (mod 3)
}
