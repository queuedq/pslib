#include <template.h>

// 1-based index
struct fenwick_tree {
  vector<lld> A;

  fenwick_tree(int size) { A.resize(size+1); }

  void add(int i, lld x) {
    for (; i < A.size(); i += i & -i) A[i] += x;
  }

  // Returns sum of A[1..i], or 0 if i = 0
  lld sum(int i) {
    lld s = 0;
    for (; i > 0; i -= i & -i) s += A[i];
    return s;
  }
};
