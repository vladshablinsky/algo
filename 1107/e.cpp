#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 101;
const long long INF = 1000000000 * 1ll * 1000000000;

long long f_0[MAXN][MAXN][MAXN];
long long f_1[MAXN][MAXN][MAXN];
long long ans[MAXN][MAXN];
int a[MAXN];

int main() {
  int n;
  string s;
  cin >> n;
  cin >> s;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      ans[i][j] = -INF;
      for (int k = 0; k <= n; ++k) {
        f_0[i][j][k] = -INF;
        f_1[i][j][k] = -INF;
      }
    }
    if (s[i] == '0') {
      f_0[i][i][1] = 0;
    } else {
      f_1[i][i][1] = 0;
    }
    ans[i][i] = a[0];
  }

  //cout << "ok till here\n";

  for (int substr_len = 2; substr_len <= n; ++substr_len) {
    for (int l = 0; l + substr_len - 1 < n; ++l) {
      for (int k = 1; k <= substr_len; ++k) {
        for (int m = l; m + 1 <= l + substr_len - 1; ++m) {
          f_0[l][l + substr_len - 1][k] = max(f_0[l][l + substr_len - 1][k],
              ans[l][m] + f_0[m + 1][l + substr_len - 1][k]);

          f_1[l][l + substr_len - 1][k] = max(f_1[l][l + substr_len - 1][k],
              ans[l][m] + f_1[m + 1][l + substr_len - 1][k]);

          if (k && s[l] == '0') {
            f_0[l][l + substr_len - 1][k] = max(f_0[l][l + substr_len - 1][k],
              (l + 1 <= m ? ans[l + 1][m] : 0) + f_0[m + 1][l + substr_len - 1][k - 1]);
          }

          if (k && s[l] == '1') {
            f_1[l][l + substr_len - 1][k] = max(f_1[l][l + substr_len - 1][k],
              (l + 1 <= m ? ans[l + 1][m] : 0) + f_1[m + 1][l + substr_len - 1][k - 1]);
          }
        }
        ans[l][l + substr_len - 1] = max(ans[l][l + substr_len - 1],
            f_0[l][l + substr_len - 1][k] + (k ? a[k - 1] : 0));

        ans[l][l + substr_len - 1] = max(ans[l][l + substr_len - 1],
            f_1[l][l + substr_len - 1][k] + (k ? a[k - 1] : 0));
      }
    }

    //if (substr_len==2)
    //for (int l = 0; l + substr_len - 1 < n; ++l) {
    //  for (int k = 1; k <= substr_len; ++k) {
    //    if (f_0[l][l+substr_len-1][k] > 0) {
    //      printf("f_0[%d][%d][%d] = %lld ", l, l+substr_len-1,k, f_0[l][l+substr_len-1][k]);
    //    }
    //    if (f_1[l][l+substr_len-1][k] > 0) {
    //      printf("f_1[%d][%d][%d] = %lld ", l, l+substr_len-1,k, f_1[l][l+substr_len-1][k]);
    //    }
    //  }
    //  printf("\n");
    //  if (ans[l][l+substr_len-1] > 0) {
    //    printf("ans[%d][%d] = %lld ", l, l+substr_len-1, ans[l][l+substr_len-1]);
    //  }
    //}
    //printf("\n");
  }


  cout << ans[0][n - 1] << "\n";
  return 0;
}
