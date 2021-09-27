// http://boj.kr/47f2c20f58cb447193c170d49a9f8f5c
#include <template.h>

// 1-based index
struct fenwick_tree {
  vector<lld> F;
  fenwick_tree(int sz) { F.resize(sz+1); }

  void add(int i, lld x) {
    for (; i<F.size(); i += i&-i) F[i] += x;
  }

  lld sum(int i) { // [1, i]
    lld s = 0;
    for (; i>0; i -= i&-i) s += F[i];
    return s;
  }
};
