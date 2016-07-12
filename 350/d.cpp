#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int MAX_N = 1e5 + 5;

int a[MAX_N], b[MAX_N];
int n, k;

bool check(long long t) {
  double need_to_add = 0;
  for (int i = 0; i < n; ++i) {
    need_to_add += max((t * 1.0 * a[i] - b[i]), 0.0);
    if (need_to_add > k) {
      return false;
    }
  }
  return true;
}

int main() {
  scanf("%d%d", &n, &k);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &b[i]);
  }

  long long ans = 0;

  long long l = 0;
  long long r = 1e15;
  while (l <= r) {
    long long m = (l + r) / 2;
    if (check(m)) {
      ans = max(ans, m);
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  cout << ans << "\n";
  return 0;
}
