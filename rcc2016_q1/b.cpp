#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 1e5 + 20;

int a[MAXN];
bool lighted[MAXN];

void solve() {
  int n;
  int h;
  scanf("%d%d", &n, &h);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    lighted[i] = (t == 1);
  }

  int ans = 0;
  if (lighted[0] == 0) {
    ++ans;
    lighted[0] = 1;
  }
  if (lighted[n - 1] == 0) {
    ++ans;
    lighted[n - 1] = 1;
  }

  int prev_lighted = 0;
  for (int i = 0; i < n; ++i) {
    if (lighted[i]) {
      prev_lighted = 0;
    } else {
      prev_lighted += a[i];
    }

    if (prev_lighted >= h) {
      ++ans;
      prev_lighted = 0;
    }
  }
  printf("%d\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
