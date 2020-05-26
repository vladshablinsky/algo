#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 200005;

int a[2 * MAXN];
long long pref[2 * MAXN];
long long sum_hugs[2 * MAXN];

int main() {
  int n;
  long long x;
  scanf("%d%lld", &n, &x);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    a[n + i] = a[i];
    pref[i] = pref[i - 1] + a[i];
    sum_hugs[i] = sum_hugs[i - 1] + a[i] * 1ll * (a[i] + 1) / 2;
  }
  for (int i = n + 1; i <= 2 * n; ++i) {
    pref[i] = pref[i - 1] + a[i];
    sum_hugs[i] = sum_hugs[i - 1] + a[i] * 1ll * (a[i] + 1) / 2;
  }

  long long ans = 0;
  for (int start_month = 1; start_month <= n; ++start_month) {
    int l = start_month;
    int r = 2 * n;
    int end_month = r;
    while (l <= r) {
      int m = (l + r) / 2;
      // number of days if begin on start_month and end on m'th
      if (pref[m] - pref[start_month - 1] >= x) {
        end_month = min(end_month, m);
        r = m - 1;
      } else {
        l = m + 1;
      }
    }

    //cout << "start: " << start_month << ", end: " << end_month << endl;

    // there are some extra days we don't need to rest.
    long long days = pref[end_month] - pref[start_month - 1];
    long long tail_days = days - x;
    long long can_shift_start = a[start_month];
    long long can_shift_end = max(0ll, tail_days);

    long long hugs = sum_hugs[end_month] - sum_hugs[start_month - 1] - (
      tail_days * a[end_month] - tail_days * (tail_days + 1) / 2);

    //cout << "hugs: " << hugs << ", tail: " << tail_days << endl;

    long long extend = min(can_shift_start, can_shift_end);
    long long add = extend * a[end_month] - extend * (extend + 1);
    //cout << "extend: " << extend << endl;
    ans = max(ans, hugs + add);
  }
  cout << ans << "\n";
  return 0;
}
