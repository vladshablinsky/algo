#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int MAX_N = 505;
int a[MAX_N];
bool f[2][MAX_N][MAX_N];

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  f[0][0][0] = true;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }

  int num = 0;

  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= k; ++j) {
      for (int l = 0; l <= j; ++l) {
        f[i % 2][j][l] = f[(i + 1) % 2][j][l] ||
          (j - a[i] >= 0 && f[(i + 1) % 2][j - a[i]][l]) ||
          (j - a[i] >= 0 && l - a[i] >= 0 && f[(i + 1) % 2][j - a[i]][l - a[i]]);
        if (i == n && j == k) {
          num += f[i % 2][j][l];
        }
      }
    }
  }

  printf("%d\n", num);

  for (int i = 0; i <= k; ++i) {
    if (f[n % 2][k][i]) {
      printf("%d ", i);
    }
  }
  printf("\n");

  return 0;
}
