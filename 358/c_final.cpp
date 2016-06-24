#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <cstdlib>

using namespace std;

const int MAXN = 1e5 + 5;

int parent[MAXN];
int value[MAXN];
int cost_enter[MAXN];
/* (i, cost) */
vector<int> g[MAXN];
int res = 0;

int subtree_size(int v) {
  int ans = 1;
  for (int i = 0; i < g[v].size(); ++i) {
    ans += subtree_size(g[v][i]);
  }
  return ans;
}

void dfs(int v, int cur_sum) {
  if (cur_sum > value[v]) {
    res += subtree_size(v);
    return;
  }

  for (int i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    dfs(to, max(0, cur_sum + cost_enter[to]));
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &value[i]);
  }

  for (int i = 1; i < n; ++i) {
    int v_par, cost;
    scanf("%d%d", &v_par, &cost);
    --v_par;
    g[v_par].push_back(i);
    cost_enter[i] = cost;
    parent[i] = v_par;
  }

  dfs(0, 0);
  cout << res << "\n";

  return 0;
}

