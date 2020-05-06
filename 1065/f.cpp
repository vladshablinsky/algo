#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1000005;
vector<int> g[MAXN];
int val_at_v[MAXN];
int ans = 0;

pair<int, int> dfs(int v, int k, vector<int> &path) {
  path.push_back(v);
  int min_depth_subtr = MAXN;
  int max_subtr = 0;

  if (g[v].empty()) {
    val_at_v[v] = 1;
    min_depth_subtr = 0;
  }

  for (auto to: g[v]) {
    auto subtr = dfs(to, k, path);
    max_subtr = max(max_subtr, subtr.first);
    min_depth_subtr = min(min_depth_subtr, subtr.second + 1);
  }

  // propagate up
  if (min_depth_subtr < k) {
    int cnt_up = min(k - min_depth_subtr, (int)path.size() - 1);
    if (cnt_up) {
      val_at_v[*(path.rbegin() + cnt_up)] += val_at_v[v];
      val_at_v[v] = 0;
    }
  }

  path.pop_back();
  ans = max(ans, max_subtr + val_at_v[v]);
  return {max_subtr + val_at_v[v], min_depth_subtr};
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 2; i <= n; ++i) {
    int p_i;
    scanf("%d", &p_i);
    g[p_i].push_back(i);
  }

  vector<int> path;
  dfs(1, k, path);
  cout << ans << "\n";
  return 0;
}
