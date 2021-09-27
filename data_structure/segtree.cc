// http://boj.kr/85713670c97541b89d44c2daa7cbdb64
#include <template.h>

const int ST = 1<<20; // 1 << (int)ceil(log2(N))
lld seg[ST*2];

void update(int i, lld val) {
  seg[i+=ST] = val;
  for (i/=2; i>0; i/=2) seg[i] = seg[i*2] + seg[i*2+1];
}

lld query(int l, int r) { // [l, r]
  lld res = 0;
  for (l+=ST, r+=ST+1; l<r; l/=2, r/=2) {
    if (l&1) res += seg[l++];
    if (r&1) res += seg[--r];
  }
  return res;
}

// usage
void usage() {
  update(3, 9); // A[3] = 9
  lld sum = query(2, 7); // sum = A[2] + ... + A[7]
}
