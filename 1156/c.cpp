#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int MAX_N = 200005;
int a[MAX_N];

bool check(int cnt, int n, int z) {
  for (int i = 0; i < cnt; ++i) {
    if (a[n - cnt + i] - a[i] < z) {
      return false;
    }
  }
  return true;
}

int main() {
  int n, z;
  scanf("%d%d", &n, &z);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  sort(a, a + n);
  int ans = 0;
  int l = 0;
  int r = n / 2;
  while (l <= r) {
    int m = (l + r) / 2;
    if (check(m, n, z)) {
      ans = max(ans, m);
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  cout << ans << "\n";
  return 0;
}
