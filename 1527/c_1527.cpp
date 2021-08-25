// https://codeforces.com/contest/1527/problem/C

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> a(n);
    unordered_map<int, vector<int>> el_idx;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    el_idx[a[i]].push_back(i);
  }

  long long ans = 0;
  for (auto& [el, idx]: el_idx) {
    if (idx.size() == 1) {
      continue;
    }

    long long sum_idx = 0;
    for (auto cur_i: idx) {
      sum_idx += (n - cur_i);
    }

    for (int i = 0; i + 1 < idx.size(); ++i) {
      sum_idx -= (n - idx[i]);
      ans += (idx[i] + 1) * sum_idx;
    }
  }
  cout << ans << "\n";
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
