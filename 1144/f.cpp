#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>

using namespace std;

const int MAXN = 200005;

int color[MAXN];
vector<int> g[MAXN];
vector<pair<int, int>> edges;

void dfs(int v, int p, bool &possible) {
  if (!possible) {
    return;
  }

  color[v] = color[p] + 1;
  color[v] -= 2 * (color[v] > 2);

  for (auto to: g[v]) {
    if (to != p) {
      if (color[to] == color[v]) {
        possible = false;
        return;
      } else if (!color[to]) {
        dfs(to, v, possible);
      }
    }
  }
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);

  bool possible = true;
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u; --v;
    g[u].push_back(v);
    g[v].push_back(u);
    edges.push_back({u, v});
  }

  dfs(0, 0, possible);
  if (!possible) {
    printf("NO\n");
  } else {
    printf("YES\n");
    for (auto &edge: edges) {
      int u, v;
      std::tie(u, v) = edge;
      if (color[u] < color[v]) {
        printf("1");
      } else {
        printf("0");
      }
    }
    printf("\n");
  }

  return 0;
}
