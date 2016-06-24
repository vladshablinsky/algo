/* *
 * Misunderstood the statement of the problem. This code solves the following
 * problem:
 *
 * Given a tree with numbers value_i written on the verteces and edges. The
 * tree is rooted and the root is vertex 1. Every vertex except 1, has an
 * incoming edge, the edge has the value written on it. For incoming edge for
 * vertex v, the value is cost_enter_v.
 *
 * The vertex v is *bad* if in v's subtree exists vertex u thus that
 * value_v < d(u,v), where d(u, v) is the sum of values written on edges on
 * the path from u to v.
 *
 * Your task is to remove as less verteces as possible thus there is no *bad*
 * verteces after removal.
 * */
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

void dfs(int v, int cur_val) {
  cur_val = min(cur_val, value[v]);
  cout << "in " << v + 1<< " CUR VAL IS " << cur_val << endl;

  for (int i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    if (cur_val >= cost_enter[to]) {
      dfs(to, cur_val - cost_enter[to]);
    } else {
      res += subtree_size(to);
    }
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

  dfs(0, 1000000000);
  cout << res << "\n";

  return 0;
}

