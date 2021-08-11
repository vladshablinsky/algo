#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
const int INF = 1000000009;
int a[MAXN];
int b[MAXN];

int days_to_earn(long long sal, long long val) {
  if (val <= 0) {
    return 0;
  }
  // add extra day if there is a remainder
  return val / sal + (val % sal != 0);
}

void solve() {
  int n, c;
  cin >> n >> c;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < n - 1; ++i) {
    cin >> b[i];
  }

  long long cur_bal = 0;
  long long ans = INF;
  long long days = 0;

  // each day try to buy computer and promote
  for (int i = 0; i < n; ++i) {
    ans = min(ans, days + days_to_earn(a[i], -cur_bal + c));
    if (i < n - 1) {
      int to_promo_days = days_to_earn(a[i], b[i] - cur_bal);
      cur_bal = cur_bal - b[i] + a[i] * to_promo_days;
      days += to_promo_days + 1; // one day for studying
    }
  }

  cout << ans << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
