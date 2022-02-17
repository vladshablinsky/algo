#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;


void solve() {
  int n;
  map<int, int> mp;

  scanf("%d", &n);
  int ans = -1;
  for (int i = 1, el = 0; i <= n; ++i) {
    scanf("%d", &el);

    if (auto prev_i = mp[el]) {
      ans = max(ans, n - i + prev_i);
    }
    mp[el] = i;
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
