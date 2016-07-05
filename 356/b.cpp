#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int a[105];
int n;

int main() {
  int pos;
  scanf("%d%d", &n, &pos);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }

  int ans = 0;
  for (int i = 1; i < n; ++i) {
    if (pos + i <= n && pos - i < 1) {
      ans += a[pos + i];
    } else if (pos + i > n && pos - i >= 1) {
      ans += a[pos - i];
    } else if (pos + i <= n && pos - i >= 1) {
      ans += 2 * (a[pos - i] & a[pos + i]);
    }
  }
  ans += a[pos];
  cout << ans << "\n";
  return 0;
}
