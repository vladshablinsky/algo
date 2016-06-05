#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

long long mabs(long long x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

void solve() {
  long long a, b, c;
  scanf("%lld%lld%lld", &a, &b, &c);
  long long area = a * b;
  long long k = max(1ll, (a * b) / (c * c));
  long long ans = c * c;
  long long min_abs = mabs(area - c * c);
  if (mabs(area - k * c * c) < min_abs) {
    min_abs = mabs(area - k * c * c);
    ans = k * c * c;
  }
  if (mabs(area - (k + 1) * c * c) < min_abs) {
    min_abs = mabs(area - (k + 1) * c * c);
    ans = (k + 1) * c * c;
  }
  printf("%lld\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
