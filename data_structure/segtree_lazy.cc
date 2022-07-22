// Range add range sum query, [l, r]
// http://boj.kr/f64e25022c194d27a381ebb4dd064f9d
// Reference: https://cp-algorithms.com/data_structures/segment_tree.html
#include <template.h>

const int ST = 1<<20; // 1 << (int)ceil(log2(N))
lld seg[ST*2], lazy[ST*2];

void push(int n, int nl, int nr) {
  seg[n*2] += lazy[n] * (nr-nl+1)/2; // sum query
  seg[n*2+1] += lazy[n] * (nr-nl+1)/2;
  lazy[n*2] += lazy[n];
  lazy[n*2+1] += lazy[n];
  lazy[n] = 0;
}

void add_range(int n, int nl, int nr, int l, int r, lld v) {
  if (nr < l || r < nl) return;
  if (l <= nl && nr <= r) {
    seg[n] += v * (nr-nl+1); // sum query
    lazy[n] += v;
    return;
  }
  push(n, nl, nr);
  int m = (nl+nr)/2;
  add_range(n*2, nl, m, l, r, v);
  add_range(n*2+1, m+1, nr, l, r, v);
  seg[n] = seg[n*2] + seg[n*2+1]; // sum query
}
void add_range(int l, int r, lld v) { add_range(1, 0, ST-1, l, r, v); }

lld query_sum(int n, int nl, int nr, int l, int r) {
  if (nr < l || r < nl) return 0;
  if (l <= nl && nr <= r) return seg[n];
  push(n, nl, nr);
  int m = (nl+nr)/2;
  return query_sum(n*2, nl, m, l, r) + query_sum(n*2+1, m+1, nr, l, r); // sum query
}
lld query_sum(int l, int r) { return query_sum(1, 0, ST-1, l, r); }

// usage
void usage() {
  add_range(3, 6, 9); // A[3] += 9, ..., A[6] += 9
  lld sum = query_sum(4, 7); // sum = A[4] + ... + A[7]
}
