#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
  long long n, m;
  cin >> n >> m;
  if (min(n, m) > 2) {
    cout << (n * m) / 2 * 2 << "\n";
  } else if (min(n, m) == 2) {
    long long len = max(n, m);
    long long ans = (len / 4) * 8 + (len % 4 == 3) * 4;
    // 4, 5, 6 combinations
    if (len % 5 == 0) {
      ans = n * m;
    } else {
      len -= 6;
      if (len >= 0) {
        ans = max(ans, (len / 4) * 8 + (len % 4 == 3) * 4 + 12);
        len -= 5;
        if (len >= 0) {
          ans = max(ans, (len / 4) * 8 + (len % 4 == 3) * 4 + 22);
        }
        len += 5;
      }
      len += 6;

      len -= 5;
      if (len >= 0) {
        ans = max(ans, (len / 4) * 8 + (len % 4 == 3) * 4 + 10);
      }
    }
    cout << ans << "\n";
  } else {
    long long len = max(n, m);
    long long ans = (len / 6) * 6 + max(len % 6 - 3, 0ll) * 2;
    cout << ans << "\n";
  }
  return 0;
}
