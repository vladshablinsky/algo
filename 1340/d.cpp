#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100005;

vector<int> g[MAXN];
bool used[MAXN];

vector<pair<int, int>> ans;
// when go down from p to v with income_val we expect to go up with income_val
void dfs(int v, int p, int income_val) {
  //cout << "v: " << v << ", p: " << p << ", income: " << income_val << endl;
  ans.push_back({v, income_val});

  int cnt_children = g[v].size();
  if (p != -1) {
    cnt_children--;
  }

  // we know we use -> {v, incove_val - 1} before going up
  int cnt_less = min(cnt_children, income_val - 1);
  int cnt_greater = cnt_children - cnt_less;

  // cout << "cnt_less: " << cnt_less << ", cnt_greater: " << cnt_greater << endl;

  int cur_gr = 0;
  int i;
  for (i = 0; i < g[v].size() && cur_gr != cnt_greater; ++i) {
    if (g[v][i] == p) {
      continue;
    }
    // will get back with income_val + cur_gr + 1
    dfs(g[v][i], v, income_val + cur_gr + 1);
    ++cur_gr;
  }

  if (p == -1) {
    return;
  }

  ans.push_back({v, income_val - 1 - cnt_less});
  // decrease first, so that we return
  for (; i < g[v].size(); ++i) {
    if (g[v][i] == p) {
      continue;
    }
    dfs(g[v][i], v, income_val - cnt_less);
    --cnt_less;
  }
  ans.push_back({p, income_val});
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    g[from].push_back(to);
    g[to].push_back(from);
  }

  dfs(1, -1, 0);
  cout << ans.size() << "\n";
  for (auto el: ans) {
    cout << el.first << " " << el.second << "\n";
  }
  return 0;
}
