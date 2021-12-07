#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 200005;
int a[MAXN];
int b[MAXN];

bool check(int cnt, int n) {
  int cnt_collected = 0;
  for (int i = 0; i < n; ++i) {
    if (cnt_collected <= b[i] && cnt - 1 - cnt_collected <= a[i]) {
      ++cnt_collected;
    }
    if (cnt_collected == cnt) {
      return true;
    }
  }
  return false;
}

void solve() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &a[i], &b[i]);
  }

  int l = 1;
  int r = n;
  int ans = 0;
  while (l <= r) {
    int m = (l + r) / 2;
    if (check(m, n)) {
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
