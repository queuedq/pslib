#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "2_sat.cc"

TEST_CASE("2-SAT works") {
  // (a | !b) & (!a | b) & (!a | !b) & (a | !c)
  int N = 3;
  pii prob[4] = {{0, 3}, {1, 2}, {1, 3}, {0, 5}};

  two_sat S(N);
  for (int i=0; i<4; i++) S.add_clause(prob[i].first, prob[i].second);

  REQUIRE(S.solve());
  REQUIRE(S.ans[0] == false);
  REQUIRE(S.ans[1] == false);
  REQUIRE(S.ans[2] == false);
}
