#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 200005;
int a[MAXN];

void solve() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  int filled_till_i = n - 1;
  int ans = 0;

  // How much right there are
  for (int i = 1; i <= n - 1; ++i) {
    // Current is n - i - 1

    if (filled_till_i <= n - i - 1) {
      continue;
    }
    if (a[n - i - 1] != a[n - 1]) {
      filled_till_i = n - i * 2;
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
