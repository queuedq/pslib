// Lines should be aligned left to right
// => (dec slope, min query) or (inc slope, max query)
#include <template.h>

struct Line {
  lld a, b; double l = -INFINITY, r = INFINITY;
  double inter(Line L) { return -(double)(b-L.b) / (a-L.a); }
  lld get(lld x) { return a*x+b; }
  bool operator <(const Line &L) const { return r < L.r; }
};

struct CHT {
  deque<Line> dq;

  void push(lld a, lld b) {
    Line L = {a, b};
    while (sz(dq) && dq.back().inter(L) <= dq.back().l) dq.pop_back();
    if (sz(dq)) dq.back().r = L.l = dq.back().inter(L);
    dq.push_back(L);
  }

  lld min_pop(lld x) { // inc query, O*(1)
    while (dq.front().r <= x) dq.pop_front();
    return dq.front().get(x);
  }

  lld min(lld x) { // any query, O(log N)
    auto it = lower_bound(dq.begin(), dq.end(), (Line){0, 0, 0, (double)x});
    return it->get(x);
  }
};
