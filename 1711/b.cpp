#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

constexpr int kInf = 1000000000;

int solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> a(n);
  for (auto& el: a) {
    scanf("%d", &el);
  }

  vector<int> cnt_pairs_i(n, 0);
  vector<pair<int, int>> edges(m);
  for (int i = 0; i < m; ++i) {
    int f1, f2;
    scanf("%d%d", &f1, &f2);
    --f1, --f2;
    cnt_pairs_i[f1]++;
    cnt_pairs_i[f2]++;
    edges[i] = {f1, f2};
  }

  if (!(m & 1)) {
    return 0;
  }

  int min_ans = kInf;
  for (int i = 0; i < n; ++i) {
    if (cnt_pairs_i[i] & 1) {
      min_ans = min(min_ans, a[i]);
    }
  }
  for (auto [f1, f2]: edges) {
    if (!((cnt_pairs_i[f1] + cnt_pairs_i[f2]) & 1)) {
      min_ans = min(min_ans, a[f1] + a[f2]);
    }
  }
  return min_ans;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    printf("%d\n", solve());
  }
}
