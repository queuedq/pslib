// Tree compression
// - https://infossm.github.io/blog/2021/09/21/virtual-tree/
// - https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/CompressTree.h
// - BOJ 20535 최소 공통 조상과 쿼리: http://boj.kr/84d0e2f4f10d471aa6afdfdd9a6c4b5f
#include "template.h"

const int MN = 303030;
int N, Q;
vector<int> adj[MN]; // original tree
int par[MN][20], dep[MN], dfn[MN], id; // LCA

void dfs(int u, int p) {
  par[u][0] = p;
  dep[u] = dep[p]+1;
  dfn[u] = ++id;
  for (auto v: adj[u]) {
    if (v == p) continue;
    dfs(v, u);
  }
}

int lca(int u, int v) {
  if (u == v) return u;
  if (dfn[u] > dfn[v]) swap(u, v);
  for (int k=19; k>=0; k--) {
    if (dfn[u] < dfn[par[v][k]]) v = par[v][k];
  }
  return par[v][0];
}

struct CompressedTree {
  vector<int> V;
  vector<pii> adj[MN];

  void add_edge(int u, int v, int d) { adj[u].push_back({v, d}); }

  ////////////////////////////////
  // Add query handling logic here
  ////////////////////////////////
} T;

void compress_tree(vector<int> &U) { // This sorts U, be careful!!!
  int k = sz(U);
  auto &V = (T.V = U);

  sort(all(U), [](int a, int b) { return dfn[a] < dfn[b]; });
  for (int i=0; i<k-1; i++) V.push_back(lca(U[i], U[i+1]));

  sort(all(V), [](int a, int b) { return dfn[a] < dfn[b]; });
  V.erase(unique(all(V)), V.end());

  for (int i=0; i<sz(V)-1; i++) {
    int p = lca(V[i], V[i+1]);
    T.add_edge(p, V[i+1], dep[V[i+1]] - dep[p]);
  }
}

void usage() {
  cin >> N >> Q;
  for (int i=0; i<N-1; i++) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  // prepare lca
  dfs(1, 0);
  for (int k=1; k<20; k++)
    for (int u=1; u<=N; u++)
      par[u][k] = par[par[u][k-1]][k-1];

  // query
  for (int q=0; q<Q; q++) {
    int k; cin >> k;
    vector<int> U(k);
    for (int i=0; i<k; i++) cin >> U[i];

    compress_tree(U);

    ////////////////////////////////
    // Handle query here
    // Don't forget to reset the tree!!!
    ////////////////////////////////
  }
}
