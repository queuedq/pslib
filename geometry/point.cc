#pragma once
#include <template.h>

const double PI = acos(-1);

struct Point {
  lld x, y;
  Point(): x(0), y(0) {}
  Point(lld x, lld y): x(x), y(y) {}

  bool operator ==(Point a) const { return x == a.x && y == a.y; }
  bool operator !=(Point a) const { return !(*this == a); }
  bool operator <(Point a) const { return pair(x, y) < pair(a.x, a.y); }
  Point operator +(Point a) const { return {x+a.x, y+a.y}; }
  Point operator -(Point a) const { return {x-a.x, y-a.y}; }
  Point operator *(lld c) const { return {x*c, y*c}; }
  Point operator /(lld c) const { return {x/c, y/c}; }
  lld operator *(Point a) const { return x*a.x + y*a.y; }
};

// print
ostream& operator <<(ostream& os, Point a) { return os << "(" << a.x << ", " << a.y << ")"; }

// cross product stuffs
lld cross(Point a, Point b) { return a.x*b.y - a.y*b.x; }
lld ccw(Point a, Point b, Point c) { return cross(b-a, c-a); }
double area(vector<Point> P) {
  lld sum = 0;
  for (int i = 0; i < (int)P.size()-1; i++) sum += cross(P[i], P[i+1]);
  sum += cross(P.back(), P[0]);
  return abs(sum) / 2.;
}

// length and angle
double length(Point a) { return sqrt(a*a); }
lld dist2(Point a, Point b) { return (b-a)*(b-a); }
double dist(Point a, Point b) { return sqrt((b-a)*(b-a)); }
double angle(Point a, Point b) { return atan2(cross(a, b), a * b); }
