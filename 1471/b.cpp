#include <iostream>
#include <queue>

using namespace std;

void solve() {
  int n, x;
  scanf("%d%d", &n, &x);
  // Original value and the value left after division.
  // We need original value as this value is the constant to add
  // while further splitting.
  queue<pair<int, int>> q;
  int a_i;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a_i);
    q.push({a_i, a_i});
  }

  long long ans = 0;
  bool process_q = true;
  while (!q.empty()) {
    auto [orig, cur] = q.front();
    q.pop();
    if (cur % x) {
      // cout << "finishing, added " << cur << endl;
      // ans += cur;
      process_q = false;
    }

    // cout << "still processing, add " << orig << endl;
    ans += orig;
    if (process_q) {
      q.push({orig, cur / x});
    }
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
