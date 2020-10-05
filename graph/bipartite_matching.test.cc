#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "bipartite_matching.cc"

TEST_CASE("Bipartite matching works") {
  // Matching is unique for this example
  vector<vector<int>> adj(5+1);
  adj[1] = {1};
  adj[2] = {2, 3};
  adj[3] = {1, 2, 3, 5};
  adj[4] = {};
  adj[5] = {2};

  bipartite_matching B(5, 5, adj);
  B.match();

  REQUIRE(B.cnt == 4);
  REQUIRE(B.S[1] == 1);
  REQUIRE(B.S[2] == 3);
  REQUIRE(B.S[3] == 5);
  REQUIRE(B.S[4] == 0);
  REQUIRE(B.S[5] == 2);
}
