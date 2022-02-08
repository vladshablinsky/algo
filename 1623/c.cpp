#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int INF = 1e9;

bool check(const vector<int>& v, int m) {
  bool is_ok = true;

  int prev = 0; // how much is gained from prev
  int prev_prev = 0; // how much is gained from prev=prev
  for (int i = (int)v.size() - 1; i >= 2; --i) {
    if (v[i] + prev + prev_prev * 2 < m) {
      is_ok = false;
      break;
    }

    int propagate_self = min(v[i], max(0, v[i] + prev + prev_prev * 2 - m)) / 3;

    prev_prev = prev;
    prev = propagate_self;
  }

  is_ok &= (v[0] + prev * 2 >= m && v[1] + prev + prev_prev * 2 >= m);
  return is_ok;
}

void solve() {
  int n;
  scanf("%d", &n);

  vector<int> v(n);
  int mn = INF;
  int mx = 1;
  for (auto& el: v) {
    scanf("%d", &el);
    mn = min(mn, el);
    mx = max(mx, el);
  }

  int l = mn;
  int r = mx;
  int ans = mn;
  while (l <= r) {
    int m = (l + r) / 2;

    // cout << "try: " << m << endl;

    if (check(v, m)) {
      // cout << "ok" << endl;
      ans = max(ans, m);
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  printf("%d\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
