#include <template.h>

// Range max query
struct segtree {
  vector<lld> seg;
  int size;

  segtree(int sz) {
    size = 1 << (int)ceil(log2(sz));
    seg = vector<lld>(size*2, LLONG_MIN);
  }

  void update(int i, lld val) {
    seg[size+i] = val;
    for (int n = (size+i)/2; n > 0; n /= 2) {
      seg[n] = max(seg[n*2], seg[n*2+1]);
    }
  }

  // query [l, r]
  lld query(int l, int r) { return query(1, 0, size-1, l, r); }
  lld query(int n, int nl, int nr, int l, int r) {
    if (nr < l || r < nl) return LLONG_MIN;
    if (l <= nl && nr <= r) return seg[n];
    int mid = (nl+nr)/2;
    return max(query(n*2, nl, mid, l, r), query(n*2+1, mid+1, nr, l, r));
  }
};
