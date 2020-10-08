#include <template.h>

void compress(vector<lld> &xs) {
  sort(xs.begin(), xs.end());
  xs.resize(unique(xs.begin(), xs.end())- xs.begin());
}

int idx(lld x, const vector<lld> &xs) {
  return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
}
