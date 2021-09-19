#include <iostream>
#include <cstdio>

using namespace std;

long long closest_time(long long p, long long x) {
  return (x - p % x) % x;
}

void solve() {
  long long p, a, b, c;
  scanf("%lld%lld%lld%lld", &p, &a, &b, &c);
  long long ans = min(closest_time(p, a), min(closest_time(p, b), closest_time(p, c)));
  printf("%lld\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}

