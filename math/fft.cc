// References
// - https://blog.myungwoo.kr/54
// - http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
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

vector<lld> multiply(const vector<lld> &a, const vector<lld> &b) {
  vector<cpx> fa(all(a)), fb(all(b));
  int m = sz(a) + sz(b) - 1;
	int L = 32 - __builtin_clz(m), n = 1 << L;

  fa.resize(n); fb.resize(n);

  fft(fa, 0); fft(fb, 0);
  for (int i=0; i<n; i++) fa[i] *= fb[i];
  fft(fa, 1);

  vector<lld> res(n);
  for (int i=0; i<n; i++) res[i] = (lld)round(fa[i].real());
  return res;
}
