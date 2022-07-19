#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> v(n);
  for (auto& el: v) {
    scanf("%d", &el);
  }

  long long ans = 0;
  for (int i = 1; i + 1 < n; i+=2) {
    int max_neigh = max(v[i - 1], v[i + 1]);
    if (max_neigh >= v[i]) {
      ans += (max_neigh - v[i]) + 1;
    }
  }

  // even
  if (!(n & 1)) {
    vector<long long> v1 = {0};
    for (int i = 1; i + 1 < n; i+=2) {
      v1.push_back(v1.back());
      int max_neigh = max(v[i - 1], v[i + 1]);
      if (max_neigh >= v[i]) {
        v1.back() += (max_neigh - v[i]) + 1;
      }
    }
    vector<long long> v2 = {0};
    for (int i = 1; n - i - 2 >= 0; i += 2) {
      v2.push_back(v2.back());
      int max_neigh = max(v[n - i - 2], v[n - i]);
      if (max_neigh >= v[n - i - 1]) {
        v2.back() += (max_neigh - v[n - i - 1]) + 1;
      }
    }
    std::reverse(v2.begin(), v2.end());
    long long ans2 = v1.front() + v2.front();
    for (int i = 0; i < v1.size(); ++i) {
      ans2 = min(ans2, v1[i] + v2[i]);
    }
    ans = min(ans, ans2);
  }
  printf("%lld\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
