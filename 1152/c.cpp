#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
  int a, b;
  cin >> a >> b;
  if (b < a) {
    swap(a, b);
  }

  if (a == b) {
    cout << "0\n";
    return 0;
  }

  int t = (b - a);
  int k = (a + t - 1) / t;
  int lcm = (k + 1) * t; // if a = k * t and b = (k + 1) * t
  int ans = k * t - a;

  auto try_divisor = [&](int div) {
    int j = k * t - t / div;
    if (j <= k * t - a && j >= 1) {
      if (lcm == k * t - j + t) {
        ans = min(ans, k * t - j - a);
      } else if (lcm > k * t - j + t) {
        lcm = k * t - j + t;
        ans = k * t - j - a;
      }
    }
  };

  // try the case when
  // 1) a_j = k * t - j and b_j = (k + 1) * t - j
  // 2) lcm(a_j, b_j) < lcm(k*t, (k+1)*t)
  for (int i = 1; i * i <= t; ++i) {
    if (t % i == 0) {
      try_divisor(i);
      try_divisor(t / i);
    }
  }

  cout << ans << "\n";
  return 0;
}
