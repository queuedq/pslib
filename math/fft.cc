// References
// - https://blog.myungwoo.kr/54
// - http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
// - https://usaco.guide/adv/fft?lang=cpp
#include <template.h>

using cpx = complex<double>;
const double PI = acos(-1);

// Part 1: sort by reversed-binary order
// Part 2: simulate divide and conquer
void fft(vector<cpx> &f, bool inv){
  int n = f.size();

  for (int i=1, j=0; i<n; i++) {
    int bit = n/2;
    for (; j>=bit; bit/=2) j -= bit;
    j += bit;
    if (i < j) swap(f[i], f[j]);
  }

  for (int k=2; k<=n; k*=2) {
    double t = 2*PI/k * (inv ? -1 : 1);
    cpx z(cos(t), sin(t)); // z^k = 1
    for (int i=0; i<n; i+=k) {
      cpx zs = 1;
      for (int j=0; j<k/2; j++) {
        cpx u = f[i+j], v = f[i+j + k/2] * zs;
        f[i+j] = u + v;
        f[i+j + k/2] = u - v;
        zs *= z;
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
