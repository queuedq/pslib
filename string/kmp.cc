// Reference: https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/KMP.h
#include <template.h>

vector<int> failure(const string &S) {
  vector<int> pi(S.size());
  for (int i=1; i<S.size(); i++) {
    int k = pi[i-1];
    while (k && S[i] != S[k]) k = pi[k-1];
    pi[i] = k + (S[i] == S[k]);
  }
  return pi;
}

// don't use when P is empty
vector<int> kmp(const string &S, const string &P) {
  int s = S.size(), p = P.size();
  auto pi = failure(P+'\0'+S);
  vector<int> res;
  for (int i=p+1; i<s+p+1; i++) {
    if (pi[i] == p) res.push_back(i-p*2);
  }
  return res;
}
