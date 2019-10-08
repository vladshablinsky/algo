#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 300004;
const int INF = 1e9;
const int MAXP = 19;

int a[MAXN];
int f[MAXN][MAXP];
int g[MAXN][MAXP];
int last_set_idx[MAXP];

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  for (int j = 0; j < MAXP; ++j) {
    last_set_idx[j] = INF;
  }

  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j < MAXP; ++j) {
      f[i][j] = INF;
      g[i][j] = INF;
      if (a[i] & (1 << j)) {
        g[i][j] = last_set_idx[j];
        f[i][j] = g[i][j];
        last_set_idx[j] = i;
      }
    }
  }

  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j < MAXP; ++j) {
      for (int k = 0; k < MAXP; ++k) {
        if (g[i][k] < n) {
          f[i][j] = min(f[i][j], f[g[i][k]][j]);
        }
      }

    }
  }


  for (int i = 0; i < q; ++i) {
    int l, r;
    cin >> l >> r;
    --l; --r;
    int ans = INF;
    for (int j = 0; j < MAXP; ++j) {
      if (a[r] & (1 << j)) {
        ans = min(ans, f[l][j]);
      }
    }
    if (ans <= r) {
      printf("Shi\n");
    } else {
      printf("Fou\n");
    }
  }
  return 0;
}
