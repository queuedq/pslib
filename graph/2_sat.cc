#include "template.h"

struct two_sat {
  int n; // number of nodes, i.e. (number of variables) * 2
  vector<vector<int>> g, gt; // 0-based, even: x, odd: !x / transpose of g
  vector<bool> vst;
  vector<int> ord, comp;
  vector<bool> ans;

  two_sat(
    int n,
    vector<vector<int>> g,
    vector<vector<int>> gt
  ): n(n), g(g), gt(gt) {}

  void dfs1(int u) {
    if (vst[u]) return;
    vst[u] = true;
    for (int v: g[u]) dfs1(v);
    ord.push_back(u);
  }

  void dfs2(int u, int cl) {
    comp[u] = cl;
    for (int v: gt[u]) {
      if (comp[v] == -1) dfs2(v, cl);
    }
  }

  bool solve() {
    // topo-sort
    vst.assign(n, false);
    for (int i=0; i<n; ++i) {
      if (!vst[i]) dfs1(i);
    }
    reverse(ord.begin(), ord.end());

    // scc
    comp.assign(n, -1);
    for (int i=0, j=0; i<n; ++i) {
      int u = ord[i];
      if (comp[u] == -1) dfs2(u, j++);
    }

    // solve
    ans.assign(n/2, false);
    for (int i=0; i<n; i+=2) {
      if (comp[i] == comp[i+1]) return false;
      ans[i/2] = comp[i] > comp[i+1];
    }
    return true;
  }
};
