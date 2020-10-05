#include <template.h>

const double PI = acos(-1);

struct Point {
  lld x, y;
  Point(lld x, lld y): x(x), y(y) {}
  double length();
};
bool operator==(Point a, Point b) { return a.x == b.x && a.y == b.y; }
bool operator!=(Point a, Point b) { return !(a == b); }
bool operator<(Point a, Point b) { return (pll){a.x, a.y} < (pll){b.x, b.y}; }
Point operator+(Point a, Point b) { return {a.x + b.x, a.y + b.y}; }
Point operator-(Point a, Point b) { return {a.x - b.x, a.y - b.y}; }
Point operator*(lld c, Point a) { return {c * a.x, c * a.y}; }
lld operator*(Point a, Point b) { return a.x * b.x + a.y * b.y; }
ostream& operator<<(ostream& os, Point a) { os << "(" << a.x << ", " << a.y << ")"; return os; }

lld cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
lld ccw(Point a, Point b, Point c) { return cross(b - a, c - a); }

double Point::length() { return sqrt(*this * *this); }
double angle(Point a, Point b) {
  if (a == Point(0, 0) || b == Point(0, 0))
    throw invalid_argument("angle: arguments should not be zero.");
  return atan2(a * b, cross(a, b));
}
