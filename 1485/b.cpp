#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 100005;
int a[MAXN];
long long pref[MAXN];

int main() {
  int n, q, k;
  scanf("%d%d%d", &n, &q, &k);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  a[n + 1] = k + 1;

  for (int i = 1; i <= n; ++i) {
    pref[i] = pref[i - 1] + (a[i + 1] - a[i] - 1) + (a[i] - a[i - 1] - 1);
  }

  for (int i = 0; i < q; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    // in the middle stays the same. On the borders
    // able to increase/decrese to min/max correspondingly.

    if (l == r) {
      printf("%d\n", k - 1);
    } else {
      long long ans = max(0ll, pref[r - 1] - pref[l]);
      ans += (k - a[r - 1] - 1); // can do a[r - 1] + 1 ... k except a[r]
      ans += a[l + 1] - 2; // can do 1 ... a[l + 1] - 1 except a[l]
      // cout << mid << endl;
      printf("%lld\n", ans);
    }
  }
}
