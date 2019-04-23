#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

long long gcd(long long a, long long b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

void solve(long long a, long long b, long long len, long long &mn, long long &mx) {
  long long step;
  if (a > b) {
    step = len - (a - b);
  } else {
    step = b - a;
  }

  // cout << "a = " << a << ", b = " << b << ", step = " << step << endl;

  // if (step == 0) {
  //   mn = 1;
  //   mx = len;
  //   return;
  // }

  long long res = len / gcd(len, step);

  // cout << "len = " << len << ", step = " << step << ", res = " << res << endl;

  mn = min(mn, res);
  mx = max(mx, res);
}

int main() {
  long long n, k;
  long long a, b;
  cin >> n >> k;
  cin >> a >> b;

  if (n == 1 && k == 1) {
    cout << 1 << " " << 1 << "\n";
    return 0;
  }

  long long mn = 1e18;
  long long mx = 1;

  for (long long cur_b = b, cur_next_b = k - b; cur_b < n * k; cur_b += k, cur_next_b += k) {
  // cout << "cur_b = " << cur_b << ", cur_next_b = " << cur_next_b << endl;
    solve(a, cur_b, n * k, mn, mx);
    solve(k - a, cur_b, n * k, mn, mx);
  }
  cout << mn << " " << mx << "\n";
  return 0;
}
