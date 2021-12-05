#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);
  vector<long long> v(n);
  for (auto& el: v) {
    scanf("%lld", &el);
  }

  long long ans = 0;
  long long max_left = 1;
  long long mult = 1;
  for (int i = 0; i < n; ++i) {
    while(v[i] % 2 == 0) {
      v[i] /= 2;
      mult *= 2;
    }
    max_left = max(max_left, v[i]);
    ans += v[i];
  }
  ans -= max_left;
  ans += max_left * mult;
  printf("%lld\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
