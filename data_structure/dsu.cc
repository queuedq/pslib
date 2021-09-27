#include <template.h>

struct disjoint_set {
  vector<int> p, s;

  disjoint_set(int sz) {
    p.resize(sz); s.resize(sz);
    for (int i=0; i<sz; i++) { p[i] = i; s[i] = 1; }
  }

  int find(int x) {
    if (x == p[x]) return x;
    return p[x] = find(p[x]);
  }

  void merge(int x, int y) { // note: "union" is a keyword in C++
    x = find(x); y = find(y);
    if (x == y) return;
    if (s[x] < s[y]) swap(x, y);
    p[y] = x;
    s[x] += s[y];
  }

  // utility functions
  bool same(int x, int y) { return find(x) == find(y); }
  int size(int x) { return s[find(x)]; }
};
