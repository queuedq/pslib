#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "bipartite_matching.cc"

TEST_CASE("Bipartite matching works") {
  // Matching is unique for this example
  N = 5, M = 4;
  adj[1] = {1};
  adj[2] = {2, 3};
  adj[3] = {1, 2, 3, 5};
  adj[4] = {};
  adj[5] = {2};

  int cnt = 0;
  for (int u=1; u<=N; u++) {
    fill(vst+1, vst+N+1, 0);
    cnt += match(u);
  }

  REQUIRE(cnt == 4);
  REQUIRE(S[1] == 1);
  REQUIRE(S[2] == 3);
  REQUIRE(S[3] == 5);
  REQUIRE(S[4] == 0);
  REQUIRE(S[5] == 2);
}
