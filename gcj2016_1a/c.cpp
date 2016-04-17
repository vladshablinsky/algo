#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 1005;


bool used[MAXN];
int a[MAXN];
bool adj_m[MAXN][MAXN];
// loops with two vertices
vector<pair<int, int> > loops;
// adjacency list with direct and reversed edges
vector<pair<int, int> > g[MAXN];
int n;

void init_used() {
  for (int i = 0; i < MAXN; ++i) {
    used[i] = 0;
  }
}

void init() {
  init_used();
  for (int i = 0; i < MAXN; ++i) {
    a[i] = 0;
    g[i].clear();
    for (int j = 0; j < MAXN; ++j) {
      adj_m[i][j] = 0;
    }
  }
  loops.clear();
}

int dfs(int v, int dir) {
  used[v] = true;
  int curans = 0;
  for (int i = 0; i < g[v].size(); ++i) {
    int to = g[v][i].first;
    if (g[v][i].second == dir && !used[to] &&
        ((dir == -1 && adj_m[to][v]) || (dir == 1 && adj_m[v][to]))) {
      curans = max(curans, dfs(g[v][i].first, dir));
    }
  }
  return curans + 1;
}

void solve(int id) {
  init();
  int ans = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int to;
    scanf("%d", &to);
    a[i] = to;
    adj_m[i][to] = true;
    g[i].push_back(make_pair(to, 1));
    g[to].push_back(make_pair(i, -1));
  }

  for (int i = 1; i <= n; ++i) {
    init_used();
    vector<int> circle;
    int cur_v = i;
    circle.push_back(cur_v);
    while (!used[cur_v]) {
      used[cur_v] = true;
      cur_v = a[cur_v];
      circle.push_back(cur_v);
    }

    if (circle[0] == circle.back()) {
      ans = max(ans, (int)circle.size() - 1);
    }
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (adj_m[i][j] && adj_m[j][i]) {
        loops.push_back(make_pair(i, j));
        adj_m[i][j] = adj_m[j][i] = 0;
      }
    }
  }

  //for (int i = 0; i < loops.size(); ++i) {
    //cout << " new loop " << loops[i].first << " " << loops[i].second << endl;
  //}

  int curans = 0;
  init_used();
  for (int i = 0; i < loops.size(); ++i) {
    int v = loops[i].first;
    int u = loops[i].second;
    int p1 = dfs(u, -1);
    int p2 = dfs(v, -1);
    curans += p1 + p2;
  }
  ans = max(ans, curans);

  printf("Case #%d: %d\n", id, ans);
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve(i + 1);
  }
  return 0;
}
