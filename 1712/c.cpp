#include <iostream>
#include <cstdio>
#include <unordered_set>
#include <vector>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);

  vector<int> v(n);
  for (auto& el: v) {
    scanf("%d", &el);
  }

  int ans = n;
  int l = 0;
  int r = n;

  auto check = [&](int k) {
    unordered_set<int> st;
    for (int i = 0; i < k; ++i) {
      st.insert(v[i]);
    }
    int last = 0;
    for (int i = k; i < n; ++i) {
      int cur = v[i];
      if (st.count(v[i])) {
        cur = 0;
      }
      if (cur < last) {
        return false;
      }
      last = cur;
    }
    ans = min(ans, (int)st.size());
    return true;
  };

  while (l <= r) {
    int m = (l + r) / 2;
    if (check(m)) {
      r = m - 1;
    } else {
      l = m + 1;
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
