#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 5;

vector<int> g[MAXN];
bool used[MAXN];
bool has_loop;

void dfs(int x, int p) {
  used[x] = true;
  for (int i = 0; i < g[x].size(); ++i) {
    int to = g[x][i];
    if (used[to] == true && p != to) {
      has_loop = true;
    }
    if (!used[to]) {
      dfs(to, x);
    }
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int v, u;
    scanf("%d%d", &v, &u);
    --v, --u;
    g[v].push_back(u);
    g[u].push_back(v);
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    has_loop = false;
    dfs(i, -1);
    if (!has_loop) {
      ++ans;
    }
  }
  cout << ans << "\n";
  return 0;
}
