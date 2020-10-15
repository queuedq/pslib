#include <template.h>

const double PI = acos(-1);

template <class T>
struct Point {
  T x, y;
  Point(): x(0), y(0) {}
  Point(T x, T y): x(x), y(y) {}

  bool operator ==(Point a) const { return x == a.x && y == a.y; }
  bool operator !=(Point a) const { return !(*this == a); }
  bool operator <(Point a) const { return pair(x, y) < pair(a.x, a.y); }
  Point operator +(Point a) const { return {x+a.x, y+a.y}; }
  Point operator -(Point a) const { return {x-a.x, y-a.y}; }
  Point operator *(T c) const { return {x*c, y*c}; }
  Point operator /(T c) const { return {x/c, y/c}; }
  T operator *(Point a) const { return x*a.x + y*a.y; }
};

template <class T>
ostream& operator <<(ostream& os, Point<T> a) {
  return os << "(" << a.x << ", " << a.y << ")";
}
template <class T>
lld cross(Point<T> a, Point<T> b) { return a.x*b.y - a.y*b.x; }
template <class T>
lld ccw(Point<T> a, Point<T> b, Point<T> c) { return cross(b-a, c-a); }

template <class T>
double length(Point<T> a) { return sqrt(a*a); }
template <class T>
double angle(Point<T> a, Point<T> b) {
  if (a == Point<T>() || b == Point<T>())
    throw invalid_argument("angle: arguments should not be zero.");
  return atan2(a * b, cross(a, b));
}
