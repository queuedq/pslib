// http://boj.kr/68ee06a3332a4cc1aba5cfb9f957f5b6
#include <template.h>

const int MN = 101010;
int D[MN];

// cost(a, d) - cost(a, c) >= cost(b, d) - cost(b, c)
lld cost(int l, int r);

// calc D[s..e] where opt in [l..r]
void dnco(int s, int e, int l, int r) {
  if (s > e) return;
  int m = (s+e)/2;
  int opt = l;
  for (int i=l; i<=min(m-1, r); i++) {
    if (cost(i+1, m) < D[m]) {
      D[m] = cost(i+1, m);
      opt = i;
    }
  }
  dnco(s, m-1, l, opt);
  dnco(m+1, e, opt, r);
}
