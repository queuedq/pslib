// http://boj.kr/df1981fcec694fa0973c5ea5269cb1e5
#include <template.h>

const int MN = 505;
const int INF = 1e9;
// 1-based index
// dst should be long long because a negative cycle can overflow it
lld N, M, dst[MN], inQ[MN], cycle[MN];
vector<pii> adj[MN];

bool SPFA(int s) { // returns false if a negative cycle exists
  fill(dst+1, dst+N+1, INF);
  fill(inQ+1, inQ+N+1, 0);
  fill(cycle+1, cycle+N+1, 0);

  dst[s] = 0;
  queue<int> Q; Q.push(s); inQ[s] = 1;
  while (!Q.empty()) {
    int u = Q.front(); Q.pop(); inQ[u] = 0;

    for (auto [v, c]: adj[u]) {
      if (dst[u] + c >= dst[v]) continue;
      dst[v] = dst[u] + c;

      if (!inQ[v]) {
        if (++cycle[v] >= N) return false;
        Q.push(v); inQ[v] = 1;
      }
    }
  }
  return true;
}
