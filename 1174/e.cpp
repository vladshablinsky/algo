#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX_N = 1e6 + 5;

int f[MAX_N][21][3];

int g(int x, int y, int n) {
  return n / ((1 << x) * (y ? 3: 1));
}

int main() {
  int n;
  cin >> n;
  int pow = 0;
  int nn = n;
  while (nn > 1) {
    nn /= 2;
    ++pow;
  }

  f[1][pow][0] = 1;
  if ((1 << (pow - 1)) * 3 <= n) {
    f[1][pow - 1][1] = 1;
  }

  for (int i = 1; i <= n - 1; ++i) {
    for (int x = 0; x <= pow; ++x) {
      for (int y = 0; y <= 1; ++y) {
        f[i + 1][x][y] = (f[i + 1][x][y] + (f[i][x][y] * 1ll * (g(x, y, n) - i)) % MOD) % MOD;
        f[i + 1][x - 1][y] = (f[i + 1][x - 1][y] + (f[i][x][y] * 1ll * (g(x - 1, y, n) - g(x, y, n))) % MOD) % MOD;
        if (y) {
          f[i + 1][x][y - 1] = (f[i + 1][x][y - 1] + (f[i][x][y] * 1ll * (g(x, y - 1, n) - g(x, y, n))) % MOD) % MOD;
        }
      }
    }
  }

  cout << f[n][0][0] << "\n";
  return 0;
}
