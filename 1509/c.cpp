#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int MAXN = 2005;
const long long INF = 1000000000 * 1ll * 1000000000;
int a[MAXN];
long long f[MAXN][MAXN];

int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  sort(a, a + n);
  long long ans = INF;
  // start

  for (int len = 1; len <= n; ++len) {
    for (int start_i = 0; start_i + len - 1 < n; ++start_i) {
      int end_i = start_i + len - 1;
      if (len == 1) {
        f[start_i][start_i] = 0;
      } else {
        f[start_i][end_i] = min(f[start_i + 1][end_i], f[start_i][end_i - 1]) +
          a[end_i] - a[start_i];
      }
    }

  }

  cout << f[0][n - 1] << "\n";
  return 0;
}
