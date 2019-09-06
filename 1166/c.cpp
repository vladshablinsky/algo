#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 200005;

int a[MAX_N];
int r[MAX_N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    if (a[i] < 0) {
      a[i] *= -1;
    }
  }

  sort(a, a + n);

  long long ans = 0;
  int r = 0;
  for (int i = 0; i < n; ++i) {
    r = max(i + 1, r);
    while (r < n && a[r] <= 2 * a[i]) {
      ++r;
    }
    ans += (r - i - 1);
  }

  cout << ans << "\n";
  return 0;
}
