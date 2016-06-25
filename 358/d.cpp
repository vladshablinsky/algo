#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1005;

int f[MAXN][MAXN][12];
int f_max[MAXN][MAXN][12];
string s1, s2;

int main() {
  int n, m, cnt_seg;
  cin >> n >> m >> cnt_seg;
  cin >> s1;
  cin >> s2;

  for (int k = 1; k <= cnt_seg; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (s1[i] == s2[j]) {
          if (i - 1 < 0 || j - 1 < 0) {
            if (k == 1) {
              f[i][j][k] = 1;
              f_max[i][j][k] = 1;
            }
          } else {
            f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k] + 1);
            if (k > 1) {
              f[i][j][k] = max(f[i][j][k], f_max[i - 1][j - 1][k - 1] + 1);
            }
            f_max[i][j][k] = max(f_max[i - 1][j][k],
                max(f_max[i][j - 1][k], f[i][j][k]));
          }
        } else {
          if (i - 1 >= 0 && j - 1 >= 0) {
            f_max[i][j][k] = max(f_max[i - 1][j][k], f_max[i][j - 1][k]);
          } else if (i - 1 >= 0) {
            f_max[i][j][k] = f_max[i - 1][j][k];
          } else if (j - 1 >= 0) {
            f_max[i][j][k] = f_max[i][j - 1][k];
          }
        }
      }
    }
  }

  cout << f_max[n - 1][m - 1][cnt_seg] << "\n";

  return 0;
}
