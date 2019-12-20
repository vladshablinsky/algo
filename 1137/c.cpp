//#pragma comment(linker, "/STACK:36777216")
#pragma GCC optimize("O3,conserve-stack")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;


const int MAXN = 100002;
const int MAXD = 52;

vector<int> g[MAXN];
vector<int> gr[MAXN];
char cost[MAXN][MAXD];
bool used[MAXN][MAXD];
int n, m, d;

pair<int, int> order[MAXN * MAXD];
int color[MAXN][MAXD];
int latest_visited_in_component[MAXN];  // last component where we visited museum x
int cur_color = 0;
int order_size = 0;

int f[MAXN * MAXD]; // f(x) -- max number of museums visited in topsort order to vertex x
int cnt_in_comp[MAXN * MAXD]; // number of museums can visit in comp

void dfs1(int v, char t) {
  used[v][t] = true;
  int next_t = (t + 1) % d;

  for (int to: g[v]) {
    if (!used[to][next_t]) {
      dfs1(to, next_t);
    }
  }
  order[order_size].first = v;
  order[order_size].second = t;
  order_size++;
}

void dfs2(int v, char t) {
  color[v][t] = cur_color;

  if (cost[v][t] == '1' && latest_visited_in_component[v] != cur_color) {
    latest_visited_in_component[v] = cur_color;
    f[cur_color]++;
    cnt_in_comp[cur_color]++;
  }

  char next_t = (t - 1 + d) % d;
  for (int &to: gr[v]) {
    if (!color[to][next_t]) {
      dfs2(to, next_t);
    }
  }
}


int main() {
  scanf("%d%d%d", &n, &m, &d);

  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u; --v;
    g[u].push_back(v);
    gr[v].push_back(u);
  }

  for (int i = 0; i < n; ++i) {
    scanf("%s", cost[i]);
  }

  // First dfs
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < d; ++j) {
      if (!used[i][j]) {
        dfs1(i, j);
      }
    }
  }

  // Second dfs
  for (int i = order_size - 1; i >= 0; --i) {
    const auto &el = order[i];
    if (!color[el.first][el.second]) {
      ++cur_color;
      dfs2(el.first, el.second);
    }
  }

  for (int i = 0; i < order_size; ++i) {
    const auto &el = order[i];
    int v = el.first;
    int t = el.second;
    int next_t = (t + 1) % d;
    for (int to: g[v]) {
      if (color[v][t] != color[to][next_t]) {
        f[color[v][t]] = max(f[color[v][t]],
            f[color[to][next_t]] + cnt_in_comp[color[v][t]]);
      }
    }
  }

  printf("%d\n", f[color[0][0]]);
  return 0;
}
