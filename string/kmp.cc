#include <template.h>

vector<int> failure(string P) {
  vector<int> pi(P.size());
  int j = 0;
  for (int i=1; i<P.size(); i++) {
    while (j > 0 && P[i] != P[j]) j = pi[j-1];
    if (P[i] == P[j]) pi[i] = ++j;
    else pi[i] = 0;
  }
  return pi;
}

vector<int> matches(string S, string P) {
  int s = S.size(), p = P.size();
  vector<int> ans;

  vector<int> pi = failure(P);
  int j = 0;
  for (int i=0; i<s; i++) {
    while (j > 0 && S[i] != P[j]) j = pi[j-1];
    if (S[i] == P[j]) {
      if (j == p-1) {
        ans.push_back(i-p+1);
        j = pi[j];
      } else {
        j++;
      }
    }
  }

  return ans;
}
