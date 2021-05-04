#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 3003;
int parent[MAXN][MAXN];
int tree_size[MAXN][MAXN];
long long f[MAXN][MAXN];

vector<int> g[MAXN];
vector<pair<int, int>> paths_with_length[MAXN];

void dfs(int v, int p, int length, int root) {
  parent[root][v] = p;
  tree_size[root][v] = 1;
  paths_with_length[length].push_back({root, v});

  for (auto to: g[v]) {
    if (to != p) {
      dfs(to, v, length + 1, root);
      tree_size[root][v] += tree_size[root][to];
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);
  vector<pair<int, int>> edges(n - 1);
  for (auto& [from, to]: edges) {
    scanf("%d%d", &from, &to);
    g[from].push_back(to);
    g[to].push_back(from);
  }

  for (int i = 1; i <= n; ++i) {
    dfs(i, -1, 0, i);
  }

  long long ans = 0;
  for (auto& [from, to]: paths_with_length[1]) {
    f[from][to] = tree_size[to][from] * 1ll * tree_size[from][to];
  }

  for (int i = 2; i <= n - 1; ++i) {
    for (auto& [from, to]: paths_with_length[i]) {
      f[from][to] = tree_size[to][from] * 1ll * tree_size[from][to] +
        max(f[parent[to][from]][to], f[from][parent[from][to]]);
    }
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      ans = max(ans, f[i][j]);
    }
  }
  cout << ans << "\n";
  return 0;
}
