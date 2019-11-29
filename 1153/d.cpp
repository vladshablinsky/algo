#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 300005;
const int INF = 1e9;

vector<int> g[MAXN];
int f[MAXN];
bool is_max[MAXN];
bool used[MAXN];

void dfs(int v) {
  if (g[v].empty()) {
    f[v] = 0;
    return;
  }

  int cnt_children = 0;
  int sum_to = 0;
  int min_to = INF;

  for (int to: g[v]) {
    ++cnt_children;
    dfs(to);
    sum_to += f[to];
    min_to = min(min_to, f[to]);
  }

  if (is_max[v]) {
    f[v] = min_to;
  } else {
    f[v] = sum_to + cnt_children - 1;
  }
}

int main() {
  int n;
  int k = 0;
  cin >> n;

  for (int i = 0; i < n; ++i) {
    cin >> is_max[i];
  }

  for (int i = 1; i < n; ++i) {
    int i_th_parent;
    cin >> i_th_parent;
    --i_th_parent;
    g[i_th_parent].push_back(i);
  }
  for (int i = 0; i < n; ++i) {
    k += (g[i].empty());
  }

  dfs(0);
  cout << k - f[0] << "\n";
  return 0;
}
