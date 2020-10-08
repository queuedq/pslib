#include <template.h>

// Range max query + range addition update
struct segtree {
  vector<lld> seg, lazy;
  int size;

  segtree(int sz) {
    size = 1 << (int)ceil(log2(sz));
    seg.resize(size*2);
    lazy.resize(size*2);
  }

  void propagate(int n, int nl, int nr) {
    seg[n] += lazy[n]; // times (nr-nl) when range sum query
    if (n < size) {
      lazy[n*2] += lazy[n];
      lazy[n*2+1] += lazy[n];
    }
    lazy[n] = 0;
  }

  void update_range(int l, int r, lld val) { update_range(1, 0, size, l, r, val); }
  void update_range(int n, int nl, int nr, int l, int r, lld val) {
    propagate(n, nl, nr);
    if (nr <= l || r <= nl) return;
    if (l <= nl && nr <= r) { lazy[n] += val; return propagate(n, nl, nr); }
    int mid = (nl+nr)/2;
    update_range(n*2, nl, mid, l, r, val);
    update_range(n*2+1, mid, nr, l, r, val);
    seg[n] = max(seg[n*2], seg[n*2+1]);
  }

  lld query(int l, int r) { return query(1, 0, size, l, r); }
  lld query(int n, int nl, int nr, int l, int r) {
    propagate(n, nl, nr);
    if (nr <= l || r <= nl) return 0;
    if (l <= nl && nr <= r) return seg[n];
    int mid = (nl+nr)/2;
    return max(query(n*2, nl, mid, l, r), query(n*2+1, mid, nr, l, r));
  }
};
