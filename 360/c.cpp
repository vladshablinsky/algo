#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 1e5 + 5;

vector<int> g[MAX_N];
bool used[MAX_N];
int colors[MAX_N];
int cnt_zero = 0;
int n, m;

void dfs(int v, int p, bool color) {
  used[v] = true;
  colors[v] = color;
  if (!color) {
    cnt_zero++;
  }

  for (int i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    if (to != p && used[to] && colors[to] == colors[v]) {
      printf("-1\n");
      exit(0);
    } else if (!used[to]) {
      dfs(to, v, !color);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      dfs(i, -1, 0);
    }
  }

  printf("%d\n", cnt_zero);
  for (int i = 0; i < n; ++i) {
    if (!colors[i]) {
      printf("%d ", i + 1);
    }
  }
  printf("\n");
  printf("%d\n", n - cnt_zero);
  for (int i = 0; i < n; ++i) {
    if (colors[i]) {
      printf("%d ", i + 1);
    }
  }
  printf("\n");

  return 0;
}
