#include <template.h>

const double PI = acos(-1);

template <class T>
struct Vec {
  T x, y;
  Vec(): x(0), y(0) {}
  Vec(T x, T y): x(x), y(y) {}

  bool operator ==(Vec a) const { return x == a.x && y == a.y; }
  bool operator !=(Vec a) const { return !(*this == a); }
  bool operator <(Vec a) const { return pair(x, y) < pair(a.x, a.y); }
  Vec operator +(Vec a) const { return {x+a.x, y+a.y}; }
  Vec operator -(Vec a) const { return {x-a.x, y-a.y}; }
  Vec operator *(T c) const { return {x*c, y*c}; }
  Vec operator /(T c) const { return {x/c, y/c}; }
  T operator *(Vec a) const { return x*a.x + y*a.y; }
};

template <class T>
ostream& operator <<(ostream& os, Vec<T> a) {
  return os << "(" << a.x << ", " << a.y << ")";
}
template <class T>
lld cross(Vec<T> a, Vec<T> b) { return a.x*b.y - a.y*b.x; }
template <class T>
lld ccw(Vec<T> a, Vec<T> b, Vec<T> c) { return cross(b-a, c-a); }

template <class T>
double length(Vec<T> a) { return sqrt(a*a); }
template <class T>
double angle(Vec<T> a, Vec<T> b) {
  if (a == Vec<T>() || b == Vec<T>())
    throw invalid_argument("angle: arguments should not be zero.");
  return atan2(a * b, cross(a, b));
}
