#include <template.h>

lld gcd(lld a, lld b) {
  while (b > 0) { a %= b; swap(a, b); }
  return a;
}

lld egcd(lld a, lld b, lld &x, lld &y) {
  if (!b) return x = 1, y = 0, a;
  lld g = egcd(b, a%b, y, x);
  return y -= a/b * x, g;
}

lld modinv(lld a, lld m) {
  lld x, y;
  egcd(a, m, x, y);
  return (x + m) % m;
}

lld modpow(lld b, lld e, lld m) {
  lld r = 1;
  for (; e; b = b*b % m, e/=2)
    if (e&1) r = r*b % m;
  return r;
}

lld phi(lld n) {
  lld res = n;
  for (lld p=2; p*p <= n; p++) {
    if (n%p == 0) res = res / p * (p-1);
    while (n%p == 0) n /= p;
  }
  if (n == 1) return res;
  return res / n * (n-1);
}

// x == r0 (mod m0), x == r1 (mod m1)
// Returns {x, lcm(m0, m1)}
pll crt(lld r0, lld m0, lld r1, lld m1) {
  lld u, v;
  egcd(m0, m1, u, v);
  lld g = u*m0 + v*m1;
  lld l = m0/g * m1;

  if (r0 % g != r1 % g) return {0, 0}; // No solution

  lld x = r0 + (r1-r0)/g * u*m0;
  x = (x%l+l) % l;
  return {x, l};
}
