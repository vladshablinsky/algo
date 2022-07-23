#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

constexpr int kMaxN = 100005;

long long a[kMaxN];
long long pref[kMaxN];
long long pref_rev[kMaxN];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    pref[i] = pref[i - 1];
    pref[i] += max(0ll, a[i - 1] - a[i]);
  }

  for (int i = n; i >= 1; --i) {
    pref_rev[i] = pref_rev[i + 1];
    pref_rev[i] += max(0ll, a[i + 1] - a[i]);
  }

  for (int i = 0; i < m; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    if (l <= r) {
      printf("%lld\n", pref[r] - pref[l]);
    } else { // l > r
      printf("%lld\n", pref_rev[r] - pref_rev[l]);
    }
  }
}
