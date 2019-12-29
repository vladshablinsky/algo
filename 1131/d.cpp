#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1005;
const int INF = 1e9;
vector<int> g[3 * MAXN];
vector<int> zero_g[2 * MAXN];
vector<int> target_g[3 * MAXN];

bool used[2 * MAXN];
int color[3 * MAXN];
int cluster_map[2 * MAXN];
int cur_cluster_v;

int n, m;
int result[3 * MAXN];

void dfs_on_zero(int v) {
  used[v] = 1;
  cluster_map[v] = cur_cluster_v;
  for (auto to: zero_g[v]) {
    if (!used[to]) {
      dfs_on_zero(to);
    }
  }
}

bool topsort_on_target(int v, vector<int> &res) {
  color[v] = 1;
  for (auto to: target_g[v]) {
    if (color[to] == 1) {
      return true;
    }
    else if (!color[to]) {
      if (topsort_on_target(to, res)) {
        return true;
      }
    }
  }
  color[v] = 2;
  res.push_back(v);
  return false;
}

int main() {
  cin >> n >> m;
  cur_cluster_v = n + m;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < m; ++j) {
      if (s[j] == '<') {
        g[n + j].push_back(i);
      } else if (s[j] == '>') {
        g[i].push_back(n + j);
      } else {
        zero_g[i].push_back(n + j);
        zero_g[n + j].push_back(i);
      }
    }
  }

  for (int i = 0; i < n + m; ++i) {
    if (zero_g[i].size() && !used[i]) {
      dfs_on_zero(i);
      ++cur_cluster_v;
    }
  }

  for (int i = 0; i < n + m; ++i) {
    int from = i;
    if (cluster_map[i]) {
      from = cluster_map[i];
    }

    for (int to: g[i]) {
      if (cluster_map[to]) {
        to = cluster_map[to];
      }
      //cout << "Target add " << from << ", " << to << endl;
      target_g[from].push_back(to);
    }
  }

  vector<int> topsorted;
  for (int i = 0; i < cur_cluster_v; ++i) {
    if (target_g[i].size() && !color[i]) {
      bool res = topsort_on_target(i, topsorted);
      if (res) {
        cout << "NO\n";
        return 0;
      }
    }
  }

  for (auto v: topsorted) {
    result[v] = 1;
    for (auto to: target_g[v]) {
      result[v] = max(result[v], result[to] + 1);
    }
  }

  cout << "YES\n";
  for (int i = 0; i < n; ++i) {
    int v = i;
    if (cluster_map[i]) {
      v = cluster_map[i];
    }
    cout << max(1, result[v]) << " ";
  }
  cout << "\n";

  for (int j = n; j < n + m; ++j) {
    int v = j;
    if (cluster_map[j]) {
      v = cluster_map[j];
    }
    cout << max(1, result[v]) << " ";
  }
  cout << "\n";

  return 0;
}

