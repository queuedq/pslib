// LineContainer
// - KACTL: https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
// - niklasb: https://github.com/niklasb/contest-algos/blob/master/convex_hull/dynamic.cpp
// - (From codeforces comment https://codeforces.com/blog/entry/65587?#comment-539201)
// - BOJ 5979 납땜하기 http://boj.kr/9eefc147b06141fa8b51676589e3855a
#include "template.h"

const lld INF = 1e18;

struct Line {
  mutable lld a, b;
  mutable double p; // right intersection
  double inter(const Line &L) const {
    if (a == L.a) return p = (b > L.b) ? INF : -INF;
    return p = (double)(L.b-b) / (a-L.a);
  }
  bool operator<(const Line &L) const { return a < L.a; }
  bool operator<(lld x) const { return p < x; }
};

struct LineContainer: multiset<Line, less<>> {
  bool bad(iterator x) { // x is under prev(x) and next(x)
    if (x == begin() || next(x) == end()) return 0;
    return !(prev(x)->p < x->p);
  }

  iterator erase_update(iterator x) {
    if (x != begin()) {
      auto l = prev(x), r = next(x);
      if (r == end()) l->p = INF; else l->inter(*r);
    } 
    return erase(x);
  }

  void insert_line(lld a, lld b) {
    auto x = insert({a, b, INF});
    if (x != begin()) prev(x)->inter(*x);
    if (next(x) != end()) x->inter(*next(x));

    if (bad(x)) x = erase_update(x);
    else {
      while (next(x) != end() && bad(next(x))) erase_update(next(x));
      while (x != begin() && bad(prev(x))) erase_update(prev(x));
    }
  }

  lld query(lld x) {
    auto l = lower_bound(x);
    if (l == end()) return -INF;
    return l->a * x + l->b;
  }
};
