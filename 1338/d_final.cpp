#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 100005;

const int PARALLEL = 0;
const int CONNECT = 1;

vector<int> g[MAXN];
// f(i, j) -- max number of parallel lines on a path from some leaf to vertex i
// where j == 0 if that path ends with parallel line, 1 -- connecting line.
int f[MAXN][2];
int ans = 0;

void update_largest(pair<int, int> &p, int val) {
  if (val > p.first) {
    p.first = val;
  }
  if (p.first > p.second) {
    swap(p.first, p.second);
  }
}

void dfs(int v, int p) {
  pair<int, int> parallel{0, 0};
  pair<int, int> connecting{0, 0};
  pair<int, int> mixed{0, 0};

  int sons = g[v].size();
  for (auto to: g[v]) {
    if (to != p) {
      dfs(to, v);
      update_largest(parallel, f[to][PARALLEL]);
      update_largest(connecting, f[to][CONNECT]);
      update_largest(mixed, max(f[to][PARALLEL], f[to][CONNECT]));
    }
  }

  f[v][PARALLEL] = connecting.second + 1;
  f[v][CONNECT] = max(connecting.second, parallel.second) + max(0, sons - 1 - (p > 0));

  //cout << "f(" << v << ") = {B:" << f[v][PARALLEL] << ", R:" << f[v][CONNECT] << "}\n";

  ans = max(ans, parallel.first + parallel.second + max(0, sons - 2));
  ans = max(ans, connecting.first + connecting.second + max(1, sons - 2));
  ans = max(ans, mixed.first + mixed.second + max(0, sons - 2));
  ans = max(ans, mixed.first + mixed.second);
  ans = max(ans, f[v][CONNECT]);
  ans = max(ans, f[v][PARALLEL]);
}

int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output_my.txt", "w", stdout);
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    g[from].push_back(to);
    g[to].push_back(from);
  }

  dfs(1, -1);
  cout << ans << "\n";
  return 0;
}
