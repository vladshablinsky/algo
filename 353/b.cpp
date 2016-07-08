#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
  int n, a, b, c, d;
  cin >> n >> a >> b >> c >> d;

  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    int mmin = max(max(a + b + i + 1, a + c + i + 1), max(b + d + i + 1, c + d + i + 1));
    int mmax = min(min(a + b + i + n, a + c + i + n), min(b + d + i + n, c + d + i + n));

    if (mmax < mmin) {
      continue;
    }

    ans += (mmax - mmin + 1);
  }
  cout << ans << "\n";
  return 0;
}
