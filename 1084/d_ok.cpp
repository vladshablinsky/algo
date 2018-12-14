#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
const int MAX_N = 3e5 + 5;

long long ans = 0;
int gas[MAX_N];
vector<pair<int, int>> g[MAX_N];
multiset<long long> f[MAX_N];

void dfs(int v, int p) {
  f[v].insert(gas[v]);
  f[v].insert(gas[v]);

  for (auto e: g[v]) {
    int to = e.first;
    int cost = e.second;
    if (to != p) {
      dfs(to, v);
      long long extra_if_from_to = *next(f[to].begin()) - cost + gas[v];
      f[v].insert(extra_if_from_to);
      f[v].erase(f[v].begin());
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
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    ans = max(ans, *f[i].begin() + *next(f[i].begin()) - gas[i]);
  }
  cout << ans << "\n";
  return 0;
}
