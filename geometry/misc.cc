#include <template.h>
#include "point.cc"

double area(vector<Point> P) {
  lld sum = 0;
  for (int i = 0; i < (int)P.size()-1; i++) sum += cross(P[i], P[i+1]);
  sum += cross(P.back(), P[0]);
  return abs(sum) / 2.;
}
