#include <template.h>

using cpx = complex<double>;
const double PI = acos(-1);

// Reference: https://blog.myungwoo.kr/54
void fft(vector<cpx> &f, bool inv){
  int n = f.size();

  // Rearrange coefficients to make f_even and f_odd form continuous intervals
  for (int i=1, j=0; i<n; i++) {
    int bit = n >> 1;
    for (; j>=bit; bit>>=1) j -= bit;
    j += bit;
    if (i < j) swap(f[i], f[j]);
  }

  // Divide and conquer
  for (int s=2; s<=n; s<<=1) { // s: polynomial size
    double t = 2*PI / s * (inv ? -1 : 1);
    cpx ws(cos(t), sin(t)); // s-th root of 1
    for (int i=0; i<n; i+=s) {
      cpx w = 1;
      for (int j=0; j<s/2; j++) { // merge
        cpx u = f[i+j], v = f[i+j + s/2] * w; // u: f_even, v: f_odd
        f[i+j] = u + v;
        f[i+j + s/2] = u - v;
        w *= ws;
      }
    }
  }

  if (inv) {
    for (int i=0; i<n; i++) f[i] /= n;
  }
}

vector<lld> multiply(const vector<lld> &a, const vector<lld> &b) {
  vector<cpx> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while (n < max(a.size(), b.size()) * 2) n <<= 1;
  fa.resize(n); fb.resize(n);

  fft(fa, false); fft(fb, false);
  for (int i=0; i<n; i++) fa[i] *= fb[i];
  fft(fa, true);

  vector<lld> res(n);
  for (int i=0; i<n; i++) res[i] = (lld)round(fa[i].real());
  return res;
}
