#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

void solve() {
  long long n, k;
  scanf("%lld%lld", &n, &k);
  --n;
  long long hours = 0;
  long long next_update = 1;
  while (next_update < k && n >= next_update) {
    ++hours;
    n -= next_update;
    next_update *= 2;
  }

  next_update = min(next_update, k);
  hours += (n + next_update - 1) / next_update;
  printf("%lld\n", hours);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
