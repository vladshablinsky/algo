#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

int t, s, q;

long long mypow(long long x, int pow) {
  long long ans = 1;
  for (int i = 0; i < pow; ++i) {
    ans *= x;
  }
  return ans;
}

long long f(int cnt) {
  long long ans = s;
  for (int i = 1; i <= cnt; ++i)
    ans += s * 1ll * mypow(q - 1, cnt);
  return ans;
}

int main() {
  int ans = 1;
  scanf("%d%d%d", &t, &s, &q);
  if (q == 2) {
    cout << t / s << "\n";
    return 0;
  }
  long long tt = 1;
  while (tt < 1000000000) {
    tt = tt * 1ll * (q - 1);
    ++ans;
  }
  int ll = 1;
  int rr = ans;
  while (ll <= rr) {
    int m = (ll + rr) / 2;
    long long res = f(m);
    if (res >= t) {
      if (m <= ans) {
        ans = m;
      }
      rr = m - 1;
    }
    else
      ll = m + 1;
  }
  cout << ans << "\n";
  return 0;
}
