#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 100005;
const int MAXK = 450;
const int INF = 1000 * 1000 * 1000 + 5;

long long f[MAXN][MAXK];
int a[MAXN];
long long pref[MAXN];

void init_f() {

}

int solve() {
  int n;
  scanf("%d", &n);

  int sqrt = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    pref[i] = pref[i - 1] + a[i];
  }

  for (int i = 0; i <= n; ++i) {
    f[i][0] = INF;
  }

  f[n][1] = a[n];
  for (int j = 2; j < MAXK; ++j) {
    f[n][j] = 0;
  }

  int max_k = 1;
  for (int i = n - 1; i >= 1; --i) {
    for (int j = 1; i + j - 1 <= n && j < MAXK; ++j) {
      f[i][j] = 0;
      // printf("(%d, %d) = %d\n",i,j,f[i][j]);

      if (i + j * (j + 1) / 2 - 1 > n) {
        continue;
      }
      long long max_prev_seg = f[i + j][j - 1];
      long long cur_seg = pref[i + j - 1] - pref[i - 1];
      f[i][j] = f[i + 1][j];

      if (cur_seg < max_prev_seg) {
        // printf("update (%d,%d), cur_seg: %d, on prev_pos: %d, max_prev: %d (%d,%d)\n",i,j,cur_seg, f[i + 1][j], max_prev_seg, i + j, j - 1);

        f[i][j] = max(f[i + 1][j], cur_seg);
      }

      if (f[i][j]) {
        max_k = max(max_k, j);
      }
    }
  }
  return max_k;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    printf("%d\n", solve());
  }
}
