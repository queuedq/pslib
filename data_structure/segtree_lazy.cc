// http://boj.kr/0666a2bbbb19489eb846633042505916
#include <template.h>

const int ST = 1<<20; // 1 << (int)ceil(log2(N))
lld seg[ST*2], lazy[ST*2];

void propagate(int n, int nl, int nr) {
  seg[n] += lazy[n] * (nr-nl+1);
  if (n < ST) {
    lazy[n*2] += lazy[n];
    lazy[n*2+1] += lazy[n];
  }
  lazy[n] = 0;
}

void add_range(int n, int nl, int nr, int l, int r, lld v) {
  propagate(n, nl, nr);
  if (nr < l || r < nl) return;
  if (l <= nl && nr <= r) {
    lazy[n] += v;
    return propagate(n, nl, nr);
  }

  int mid = (nl+nr+1) / 2;
  add_range(n*2, nl, mid-1, l, r, v);
  add_range(n*2+1, mid, nr, l, r, v);
  seg[n] = seg[n*2] + seg[n*2+1];
}

lld query(int n, int nl, int nr, int l, int r) {
  propagate(n, nl, nr);
  if (nr < l || r < nl) return 0;
  if (l <= nl && nr <= r) return seg[n];

  int mid = (nl+nr+1) / 2;
  return query(n*2, nl, mid-1, l, r) + query(n*2+1, mid, nr, l, r);
}

// overloading
void add_range(int l, int r, lld v) { add_range(1, 0, ST-1, l, r, v); }
lld query(int l, int r) { return query(1, 0, ST-1, l, r); }

// usage
void usage() {
  add_range(3, 6, 9); // A[3] += 9, ..., A[6] += 9
  lld sum = query(4, 7); // sum = A[4] + ... + A[7]
}
