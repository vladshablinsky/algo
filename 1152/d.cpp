#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1005;
int n;

pair<int, bool> f[MAXN][MAXN + MAXN];

int main() {
  cin >> n;

  for (int height = 1; height < 2 * n; ++height) {
    if (height % 2 == 0) {
      f[0][height].first = (f[1][height - 1].first + (f[1][height - 1].second == 0));
      f[0][height].second = (f[1][height - 1].second == 0);
    }
    for (int balance = 1; balance <= n; ++balance) {
      if (balance > height) {
        break;
      }
      if (balance % 2 != height % 2) {
        continue;
      }

      f[balance][height].first = (f[balance + 1][height - 1].first +
          f[balance - 1][height - 1].first) % MOD;

      if (f[balance - 1][height - 1].second + f[balance + 1][height - 1].second == 0) {
        f[balance][height].first = (f[balance][height].first + 1) % MOD;
        f[balance][height].second = true;
      }
    }
  }

  cout << (f[1][2 * n - 1].first + (f[1][2 * n - 1].second == 0)) % MOD << "\n";
  return 0;
}
