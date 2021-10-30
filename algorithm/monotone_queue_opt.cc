// Should be tested
// http://boj.kr/ad52f781bca842e38a4d1eb0ff6c39f6
#include <template.h>

const int MN = 101010;
int N, D[MN];

// cost(a, d) - cost(a, c) >= cost(b, d) - cost(b, c)
lld cost(int l, int r);

struct Line {
  lld i, d, c; // segment starts at c (cross)
  lld get(int x) { return d + cost(i+1, x); }
  bool operator <(const Line &L) const { return c < L.c; }

  int cross(Line &L) { // i < L.i
    int l = L.i - 1, r = N+1;
    while (l+1 < r) {
      int m = (l+r)/2;
      if (L.get(m) <= get(m)) r = m; // L is better
      else l = m;
    }
    return r;
  }
};
vector<Line> mq;

void add(Line L) {
  while (!mq.empty() && mq.back().cross(L) <= mq.back().c) mq.pop_back();
  if (!mq.empty()) L.c = mq.back().cross(L);
  mq.push_back(L);
}

lld get(vector<Line> &mq, int x) {
  int i = upper_bound(mq.begin(), mq.end(), (Line){0, 0, x}) - mq.begin() - 1;
  return mq[i].d + cost(mq[i].i+1, x);
}

void usage() {
  int l = 0;
  for (int i=0; i<=N; i++) {
    add({i, D[i], i});
    while (l+1 < mq.size() && mq[l+1].c <= i) l++;
    D[i] = mq[l].get(i);
  }
}
