#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MOD = 998244353;

vector<vector<int>> g;
int n, m;
vector<int> part;
vector<pair<int, int>> comp_size;

bool check_bipartite(int v, int p) {
  comp_size.back().first += 1;
  if (part[v] == -1) {
    part[v] = 0;
  }

  if (part[v] == 0) {
    comp_size.back().second += 1;
  }

  bool ok = true;
  for (int to: g[v]) {
    if (part[to] == part[v]) {
      ok = false;
    } else if (part[to] == -1){
      part[to] = part[v] ^ 1;
      ok &= check_bipartite(to, v);
    }
  }
  return ok;
}

void solve() {
  g.clear();
  comp_size.clear();
  cin >> n >> m;
  g.resize(n);
  for (int i = 0; i < m; ++i) {
    int from, to;
    cin >> from >> to;
    --from;
    --to;
    g[from].push_back(to);
    g[to].push_back(from);
  }

  part = vector<int>(n, -1);
  bool is_bipartite = true;
  for (int i = 0; i < n; ++i) {
    if (part[i] == -1) {
      comp_size.push_back({0, 0});
      is_bipartite &= check_bipartite(i, -1);
    }
  }

  if (!is_bipartite) {
    cout << "0\n";
    return;
  }

  int ans = 1;
  for (auto el: comp_size) {
    int x = el.second;
    int y = el.first - el.second;
    int cur_ans = 1;
    int sum_cur_ans = 0;
    for (int i = 0; i < x; ++i) {
      cur_ans = (cur_ans * 2) % MOD;
    }
    sum_cur_ans = (sum_cur_ans + cur_ans) % MOD;
    cur_ans = 1;
    for (int i = 0; i < y; ++i) {
      cur_ans = (cur_ans * 2) % MOD;
    }
    sum_cur_ans = (sum_cur_ans + cur_ans) % MOD;
    ans = (ans * 1ll * sum_cur_ans) % MOD;
  }
  cout << ans << "\n";
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
