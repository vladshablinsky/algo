#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAX_N = 300005;
int a[MAX_N];
int n, m;

int mabs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

bool check(int k) {
  int cur = 0;
  for (int i = 0; i < n; ++i) {
    if (cur >= a[i]) {
      if (cur > a[i] + k) {
        return false;
      }
    } else {  // cur < a[i]
      if ((a[i] + k < m) || (((a[i] + k) % m) < cur)) {
        cur = a[i];
      }
    }
  }
  return true;
}

int main() {
  scanf("%d%d", &n, &m);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  int l = 0;
  int r = m - 1;
  int ans = r;
  while (l <= r) {
    int mid = (l + r) / 2;
    if (check(mid)) {
      ans = min(ans, mid);
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  printf("%d\n", ans);
  return 0;
}
