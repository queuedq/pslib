#include "number_theory.cc"

// x == r0 (mod m0), x == r1 (mod m1)
// Returns {x, lcm(m0, m1)}
pll crt(lld r0, lld m0, lld r1, lld m1) {
  auto [u, v] = egcd(m0, m1);
  lld g = u*m0 + v*m1;
  lld l = m0/g * m1;

  if (r0 % g != r1 % g) return {0, 0}; // No solution

  lld x = r0 + (r1-r0)/g * u*m0;
  x = (x%l+l) % l;
  return {x, l};
}
