#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int kMaxN = 3003;
constexpr int kInf = 1000000000;

vector<int> possibles[kMaxN];

void init(int n) {
  for (int i = 0; i < n; ++i) {
    possibles[i].clear();
  }
}

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  init(n);
  vector<int> v(n);
  int mx = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
    mx = max(mx, v[i]);
    for (int j = 1; j <= k; ++j) {
      possibles[i].push_back(v[i] / j);
      if (possibles[i].size() > 1 && *possibles[i].rbegin() == *next(possibles[i].rbegin())) {
        possibles[i].pop_back();
      }
      if (!possibles[i].back()) {
        break;
      }
    }
    std::reverse(possibles[i].begin(), possibles[i].end());
  }

  // Try to bound all to the cut
  int res = kInf;
  for (int cut = 0; cut <= mx; ++cut) {
    int mx = 0;
    int mn = kInf;

    for (int i = 0; i < n; ++i) {
      auto ub = std::lower_bound(possibles[i].begin(), possibles[i].end(), cut);
      if (ub == possibles[i].end()) {
        ub = prev(possibles[i].end());
      }

      mx = max(mx, *ub);
      mn = min(mn, *ub);
    }
    res = min(res, mx - mn);
  }
  printf("%d\n", res);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
