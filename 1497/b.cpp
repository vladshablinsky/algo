#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

void solve() {
  int n, m;
  cin >> n >> m;
  int cur_el;
  vector<int> any_rem(m + 1, false);
  for (int i = 0; i < n; ++i) {
    cin >> cur_el;
    any_rem[cur_el % m]++;
    if (cur_el % m == 0) {
      ++any_rem[m];
    }
  }

  int cnt = 0;
  for (int i = 0; i <= m / 2; ++i) {
    if (any_rem[i] || any_rem[m - i]) {
      cnt += 1;
      cnt += max(any_rem[i], any_rem[m - i])
        - min(any_rem[i], any_rem[m - i])
        - (any_rem[i] != any_rem[m - i]);
    }
  }
  cout << cnt << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
