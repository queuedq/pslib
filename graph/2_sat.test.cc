#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "2_sat.cc"

TEST_CASE("2-SAT works") {
  // (a | !b) & (!a | b) & (!a | !b) & (a | !c)
  pii prob[4] = {{0, 3}, {1, 2}, {1, 3}, {0, 5}};

  int N = 3*2;
  vector<vector<int>> g(N*2), gt(N*2);

  for (int i=0; i<4; i++) {
    g[prob[i].first^1].push_back(prob[i].second);
    g[prob[i].second^1].push_back(prob[i].first);
    gt[prob[i].first].push_back(prob[i].second^1);
    gt[prob[i].second].push_back(prob[i].first^1);
  }

  two_sat S(N, g, gt);

  REQUIRE(S.solve_2SAT());
  REQUIRE(S.assignment[0] == false);
  REQUIRE(S.assignment[1] == false);
  REQUIRE(S.assignment[2] == false);
}
