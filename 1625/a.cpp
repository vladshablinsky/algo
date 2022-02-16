#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

void solve() {
  int n, l;
  scanf("%d%d", &n, &l);
  vector<int> v(l, 0);
  for (int i = 0, el = 0; i < n; ++i) {
    scanf("%d", &el);
    for (int j = 0; j < l; ++j) {
      v[j] += ((el & (1 << j)) != 0);
    }
  }

  int ans = 0;
  for (int j = 0; j < l; ++j) {
    // cnt 1 > cnt 0, pick 1
    if (v[j] > n - v[j]) {
      ans += (1 << j);
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
