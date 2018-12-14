#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 3e5 + 5;

long long ans = 0;
int gas[MAX_N];
vector<pair<int, int>> g[MAX_N];
pair<long long, int> f[MAX_N];

void dfs(int v, int p) {
  f[v] = {gas[v], -1};

  for (auto e: g[v]) {
    int to = e.first;
    int cost = e.second;
    if (to != p) {
      dfs(to, v);
      long long extra_if_from_to = f[to].first - cost + gas[v];
      if (extra_if_from_to > f[v].first) {
        f[v].first = extra_if_from_to;
        f[v].second = to;
      }
    }
  }
  // cout << "f [ " << v << " ] = " << f[v].first << " " << f[v].second << endl;
}

void calc_ans(int v, int p, long long cur_mx) {
  long long max_extra_to_v = f[v].first;
  int come_from_to_v = f[v].second;
  ans = max(ans, cur_mx + max_extra_to_v - gas[v]);

  // cout << "in: " << v << ", from: " << p << ", cur_mx: " << cur_mx << ", max_extra_to_v: " << max_extra_to_v << ", cur_ans: " << ans << endl;

  for (auto e: g[v]) {
    int to = e.first;
    int cost = e.second;
    if (to != p) {
      if (cur_mx > max_extra_to_v) {
        calc_ans(to, v, cur_mx - cost + gas[to]);
      } else if (to != come_from_to_v) {
        calc_ans(to, v, max_extra_to_v - cost + gas[to]);
      }
      calc_ans(to, v, gas[to]);
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &gas[i]);
  }

  for (int i = 0; i < n - 1; ++i) {
    int from, to, cost;
    scanf("%d%d%d", &from, &to, &cost);
    --from;
    --to;
    g[from].push_back({to, cost});
    g[to].push_back({from, cost});
  }

  dfs(0, -1);
  calc_ans(0, -1, gas[0]);
  cout << ans << "\n";
  return 0;
}
