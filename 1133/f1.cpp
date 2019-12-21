#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 200005;

bool used[MAXN];
vector<int> g[MAXN];
vector<pair<int, int>> ans;

void bfs(int v) {
  queue<int> q;
  q.push(v);
  used[v] = true;

  while (!q.empty()) {
    int cur_v = q.front();
    q.pop();
    for (auto to: g[cur_v]) {
      if (!used[to]) {
        used[to] = true;
        q.push(to);
        ans.push_back({cur_v, to});
      }
    }
  }
}

int main() {
  int max_deg = 0;
  int max_deg_v = 0;
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].push_back(v);
    g[v].push_back(u);
    if (g[u].size() > max_deg) {
      max_deg = g[u].size();
      max_deg_v = u;
    }
    if (g[v].size() > max_deg) {
      max_deg = g[v].size();
      max_deg_v = v;
    }
  }

  bfs(max_deg_v);
  for (auto &el: ans) {
    cout << el.first + 1 << " " << el.second + 1 << "\n";
  }
  return 0;
}
