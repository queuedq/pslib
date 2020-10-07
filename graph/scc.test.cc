#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "scc.cc"

TEST_CASE("SCC works") {
  // 1 --> 2 --> 3 <-> 4
  // ^   / |     |     ^
  // |  /  |     |     |
  // | L   v     v     v
  // 5 --> 6 <-> 7 <-- 8
  //
  // Components: {1, 2, 5}, {3, 4, 8}, {6, 7}

  vector<vector<int>> adj(8+1);
  adj[1] = {2};
  adj[2] = {3, 5, 6};
  adj[3] = {4, 7};
  adj[4] = {3, 8};
  adj[5] = {1, 6};
  adj[6] = {7};
  adj[7] = {6};
  adj[8] = {4, 7};

  scc S(adj);

  REQUIRE(S.scc_id[1] == 3);
  REQUIRE(S.scc_id[2] == 3);
  REQUIRE(S.scc_id[5] == 3);

  REQUIRE(S.scc_id[3] == 2);
  REQUIRE(S.scc_id[4] == 2);
  REQUIRE(S.scc_id[8] == 2);

  REQUIRE(S.scc_id[6] == 1);
  REQUIRE(S.scc_id[7] == 1);

  auto comp = S.get_components();

  REQUIRE(comp[2] == vector({1, 2, 5}));
  REQUIRE(comp[1] == vector({3, 4, 8}));
  REQUIRE(comp[0] == vector({6, 7}));
}
