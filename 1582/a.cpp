#include <iostream>

using namespace std;

bool check(long long a, long long b, long long c, long long s) {
  if (s < 0) {
    return false;
  }
  long long k3 = min(c, s / 3);
  long long k2 = min(b, (s - k3 * 3) / 2);
  long long k1 = s - k3 * 3 - k2 * 2;
  if (k1 <= a) {
    return true;
  } else {
    return k3 && k2 + 1 <= b;
  }
}

void solve() {
  long long a, b, c;
  cin >> a >> b >> c;

  long long sum = a + b * 2 + c * 3;
  long long half_sum = (sum + 1) / 2;
  long long res = 3;
  for (int i = 0; i <= 3; ++i) {
    if (check(a, b, c, half_sum - i)) {
      res = min(res,
          max(half_sum - i, sum - half_sum + i) - min(half_sum - i, sum - half_sum + i));
    }
  }

  cout << res << "\n";
}
int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
