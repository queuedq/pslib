// https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/ConvexHull.h
// https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/HullDiameter.h
// http://boj.kr/5934a8636ec94679b19d52d936985fa7
#include <template.h>
#include "point.cc"

vector<Point> convex_hull(vector<Point> P) {
  if (P.size() <= 1) return P;
  sort(all(P));
  vector<Point> Q(P.size()+1);

  int s = 0, i = 0;
  for (auto dir: {0, 1}) {
    for (auto p: P) {
      while (i-2 >= s && ccw(Q[i-2], Q[i-1], p) <= 0) i--;
      Q[i++] = p;
    }
    s = --i; reverse(all(P));
  }

  Q.resize(i);
  if (i == 2 && Q[0] == Q[1]) Q.resize(1); // all points are same
  return Q;
}

// rotating calipers
array<Point, 2> diameter(const vector<Point> &P) {
  int n = P.size();
  pair<lld, array<Point, 2>> res = {0, {P[0], P[0]}};
  if (n == 1) return res.second;
  for (int i = 0, j = 1; i < j; i++) {
    for (;; j = (j+1) % n) {
      res = max(res, {dist2(P[i], P[j]), {P[i], P[j]}});
      if (cross(P[i+1] - P[i], P[(j+1) % n] - P[j]) <= 0) break;
    }
  }
  return res.second;
}
