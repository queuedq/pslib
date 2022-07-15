// References
// - https://blog.myungwoo.kr/54
// - http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
// - https://usaco.guide/adv/fft?lang=cpp
#include <template.h>

using cpx = complex<double>;
const double PI = acos(-1.L);

// Part 1: root memoization
// Part 2: sort by reversed-binary order
// Part 3: simulate divide and conquer
void fft(vector<cpx> &f, bool inv){
  int n = f.size(), L = 31 - __builtin_clz(n);
  static vector<complex<long double>> R(2, 1);
  static vector<cpx> rt(2, 1);
  for (static int k=2; k<n; k*=2) {
    R.resize(n); rt.resize(n);
    auto x = polar(1.0L, acos(-1.0L) / k);
    for (int i=k; i<2*k; i++) rt[i] = R[i] = (i&1) ? R[i/2] * x : R[i/2];
  }

  vector<int> rev(n);
  for (int i=0; i<n; i++) rev[i] = (rev[i/2] | (i&1)<<L) / 2;
  for (int i=0; i<n; i++) if (i < rev[i]) swap(f[i], f[rev[i]]);

  for (int k=1; k<n; k*=2) {
    for (int i=0; i<n; i+=2*k) {
      for (int j=0; j<k; j++) {
        cpx u = f[i+j], v = f[i+j+k] * (inv ? rt[j+k] : conj(rt[j+k]));
        f[i+j] = u + v;
        f[i+j+k] = u - v;
      }
    }
  }

  if (inv) {
    for (int i=0; i<n; i++) f[i] /= n;
  }
}

vector<lld> conv(const vector<lld> &a, const vector<lld> &b) {
  int m = sz(a) + sz(b) - 1;
  int L = 32 - __builtin_clz(m), n = 1<<L;

  vector<cpx> f(all(a)), g(all(b));
  f.resize(n); g.resize(n);

  fft(f, 0); fft(g, 0);
  for (int i=0; i<n; i++) f[i] *= g[i];
  fft(f, 1);

  vector<lld> res(n);
  for (int i=0; i<n; i++) res[i] = (lld)round(real(f[i]));
  return res;
}

vector<lld> conv_2in1(const vector<lld> &a, const vector<lld> &b) {
  int m = sz(a) + sz(b) - 1;
  int L = 32 - __builtin_clz(m), n = 1<<L;

  vector<cpx> f(n), g(n), h(n);
  for (int i=0; i<sz(a); i++) h[i] += a[i];
  for (int i=0; i<sz(b); i++) h[i] += cpx(0, b[i]);

  fft(h, 0);
  for (int i=0; i<n; i++) {
    int j = -i & (n-1);
    f[i] = (h[i] + conj(h[j])) / 2.;
    g[i] = (h[i] - conj(h[j])) / 2i;
  }
  for (int i=0; i<n; i++) f[i] *= g[i];
  fft(f, 1);

  vector<lld> res(n);
  for (int i=0; i<n; i++) res[i] = (lld)round(real(f[i]));
  return res;
}

vector<lld> conv_mod(const vector<lld> &a, const vector<lld> &b, lld M) {
  int m = sz(a) + sz(b) - 1;
  int L = 32 - __builtin_clz(m), n = 1<<L;
  const lld cut = 1<<15;

  vector<cpx> f(n), g(n), ol(n), os(n);
  for (int i=0; i<sz(a); i++) f[i] = cpx(a[i]/cut, a[i]%cut);
  for (int i=0; i<sz(b); i++) g[i] = cpx(b[i]/cut, b[i]%cut);

  fft(f, 0); fft(g, 0);
  for (int i=0; i<n; i++) {
    int j = -i & (n-1);
    ol[i] = (f[i] + conj(f[j])) * g[i] / 2.;
    os[i] = (f[i] - conj(f[j])) * g[i] / 2i;
  }
  fft(ol, 1); fft(os, 1);

  vector<lld> res(n);
  for (int i=0; i<n; i++) {
    lld av = (lld)round(ol[i].real());
    lld bv = (lld)round(ol[i].imag()) + (lld)round(os[i].real());
    lld cv = (lld)round(os[i].imag());
    res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
  }
  return res;
}
