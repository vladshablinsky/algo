#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 105;
int a[MAXN][MAXN];

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &a[i][j]);
      if (a[i][j] == a[i - 1][j] || a[i][j] == a[i][j - 1]) {
        a[i][j]++;
      }
      printf("%d ", a[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
