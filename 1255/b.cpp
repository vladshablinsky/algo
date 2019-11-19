#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void solve() {
  vector<pair<int, int>> v;
  vector<pair<int, int>> chains;
  int n, m;
  cin >> n >> m;
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int a_i;
    cin >> a_i;
    v.push_back({a_i, i});
    chains.push_back({i + 1, (i + 1) % n + 1});
    ans += a_i;
  }
  ans *= 2;

  if (n == 2 || m < n) {
    cout << "-1\n";
  } else {
    sort(v.begin(), v.end());
    for (int i = 0; i < m - n; ++i) {
      ans += (v[0].first + v[1].first);
      chains.push_back({v[0].second + 1, v[1].second + 1});
    }
    cout << ans << "\n";
    for (auto &el: chains) {
      cout << el.first << " " << el.second << "\n";
    }
  }
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
