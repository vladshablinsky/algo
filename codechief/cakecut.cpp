#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1505;

int a[MAXN][MAXN];
long long ans[MAXN][MAXN];
long long cnt_subsq[MAXN][MAXN];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &a[i][j]);
    }
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cnt_subsq[i][j] = cnt_subsq[i - 1][j] + cnt_subsq[i][j - 1]
        - cnt_subsq[i - 1][j - 1] + i * j;
      ans[i][j] = ans[i - 1][j] + ans[i][j - 1] - ans[i - 1][j - 1];
      if (a[i][j] == 1) {
ans
      }
    }
  }


  return 0;
}
