#include <iostream>
#include <cstdio>

using namespace std;

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    int t;
    scanf("%d", &t);
    if (t > k && i <= k) {
      ++ans;
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

