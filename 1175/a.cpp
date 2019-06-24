#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
  long long n, k;
  cin >> n >> k;
  long long ans = 0;
  while (n != 0) {
    long long r = n % k;
    if (r) {
      n -= r;
      ans += r;
    } else {
      ans++;
      n /= k;
    }
  }
  cout << ans << "\n";
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
