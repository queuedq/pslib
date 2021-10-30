// http://boj.kr/36e86b31c0b64ccaa86995c2ab2a9f36
#include <template.h>

// 1-based index
const int MN = 1005;
int N, M;
vector<int> adj[MN];

struct bipartite_matching {
  int cnt, S[MN], T[MN], vst[MN];
  // only for min vertex cover
  int rvst[MN];
  vector<int> lc, rc;

  // max matching
  bool match_node(int u) {
    if (vst[u]) return 0;
    vst[u] = 1;

    for (int v: adj[u]) {
      if (!T[v] || match_node(T[v])) {
        S[u] = v; T[v] = u;
        return 1;
      }
    }
    return 0;
  }

  int match() {
    for (int u=1; u<=N; u++) {
      fill(vst+1, vst+N+1, 0);
      cnt += match_node(u);
    }
    return cnt;
  }

  // min vertex cover
  void dfs(int u) {
    if (vst[u]) return;
    vst[u] = 1;

    for (int v: adj[u]) {
      rvst[v] = 1;
      if (T[v]) dfs(T[v]);
    }
  }
  
  void vertex_cover() {
    fill(vst+1, vst+N+1, 0);
    for (int u=1; u<=N; u++) { if (!S[u]) dfs(u); }
    for (int u=1; u<=N; u++) { if (!vst[u]) lc.push_back(u); }
    for (int v=1; v<=M; v++) { if (rvst[v]) rc.push_back(v); } // M, not N!
  }
};
