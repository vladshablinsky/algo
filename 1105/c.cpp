#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 200005;

int f[MAXN][3];
int cnt_rems[3];

int main() {
  int n, l, r;
  cin >> n >> l >> r;

  // cnt of numbers that = 0 mod 3.
  cnt_rems[0] = f[0][0] = r / 3 - (l - 1) / 3;
  cnt_rems[1] = f[0][1] = cnt_rems[0] - 1 + (l % 3 == 1) + (r % 3 != 0);
  cnt_rems[2] = f[0][2] = cnt_rems[0] - 1 + (l % 3 >= 1) + (r % 3 == 2);

  for (int i = 1; i < n; ++i) {
    for (int prev = 0; prev < 3; ++prev) {
      for (int cur = 0; cur < 3; ++cur) {
        int add = (f[i - 1][prev] * 1ll * cnt_rems[cur]) % MOD;
        f[i][(prev + cur) % 3] = (f[i][(prev + cur) % 3] + add) % MOD;
      }
    }
  }
  cout << f[n - 1][0] << "\n";
  return 0;
}
