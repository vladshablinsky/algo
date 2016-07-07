#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 505;
vector<pair<int,int> > g[MAXN][MAXN];
bool used[MAXN][MAXN];
bool f[MAXN][MAXN];
bool can_get[MAXN];
int a[MAXN];
int n, k;

void dfs(int x, int y) {
  used[x][y] = true;
  can_get[y] = true;

  for (int i = 0; i < g[x][y].size(); ++i) {
    int to_x = g[x][y][i].first;
    int to_y = g[x][y][i].second;
    if (!used[to_x][to_y]) {
      dfs(to_x, to_y);
    }
  }
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }

  f[0][0] = true;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= k; ++j) {
      int to = j - a[i];
      if (to >= 0) {
        if (f[i - 1][to]) {
          f[i][j] = true;
          g[i][j].push_back(make_pair(i - 1, to));
        }
      }
      if (f[i - 1][j]) {
        f[i][j] = true;
        g[i][j].push_back(make_pair(i - 1, j));
      }
    }
  }

  cout << "Fnk = " << f[n][k] << endl;

  if (f[n][k]) {
    dfs(n, k);
  }

  printf("0 ");
  for (int i = 1; i <= k; ++i) {
    if (can_get[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");

  return 0;
}
