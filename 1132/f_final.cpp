#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

const int MAXN = 505;

int f[MAXN][MAXN];

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output2.txt", "w", stdout);
  int n;
  string s;
  cin >> n >> s;
  for (int i = 0; i < n; ++i) {
    f[i][i] = 1;
  }

  for (int substr_len = 2; substr_len <= n; ++substr_len) {
    for (int i = 0; i + substr_len - 1 < n; ++i) {
      f[i][i + substr_len - 1] = f[i + 1][i + substr_len - 1] + 1;
      for (int j = i + 1; j <= i + substr_len - 1; ++j) {
        if (s[i] == s[j]) {
          f[i][i + substr_len - 1] = min(
              f[i][i + substr_len - 1],
              f[i + 1][j - 1] + f[j][i + substr_len - 1]
            );
        }
      }
    }
  }
  cout << f[0][n - 1] << "\n";
  return 0;
}
