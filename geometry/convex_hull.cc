// https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/ConvexHull.h
// http://boj.kr/6c3dd246a9fc489ea8ee57e2ba27ecaa
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
