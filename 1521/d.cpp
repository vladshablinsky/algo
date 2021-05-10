#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_set>
#include <tuple>

using namespace std;

const int MAXN = 100005;
vector<int> g[MAXN];

void solve() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    g[i].clear();
  }

  {
    int u, v;
    for (int i = 0; i < n - 1; ++i) {
      scanf("%d%d", &u, &v);
      g[u].push_back(v);
      g[v].push_back(u);
    }
  }

  unordered_set<int> leafs;
  vector<unordered_set<int>> children(n + 1);
  queue<pair<int, int>> q;
  q.push({1, 0});
  while (!q.empty()) {
    auto [v, p] = q.front();
    q.pop();
    for (auto to: g[v]) {
      if (to != p) {
        q.push({to, v});
        children[v].insert(to);
      }
    }
    if (children[v].empty()) {
      leafs.insert(v);
    }
  }

  cout << "leafs: ";
  for (auto leaf: leafs) {
    cout << leaf << " ";
  }
  cout << endl;

  vector<tuple<int, int, int, int>> ans;
  q.push({1, 0});
  while (!q.empty()) {
    auto [v, p] = q.front();
    q.pop();

    bool incoming = (p != 0);
    while (children[v].size() + incoming > 2) {
      int src_v = *children[v].begin();
      bool child_leaf = leafs.count(src_v);
      leafs.erase(src_v);
      int dst_v = *leafs.begin();

      if (child_leaf) {
        leafs.insert(src_v);
      }

      children[dst_v].insert(src_v);

      children[v].erase(src_v);
      leafs.erase(dst_v);

      q.push({dst_v, src_v});
      ans.push_back({v, src_v, dst_v, src_v});
    }

    for (auto to: children[v]) {
      q.push({to, v});
    }
  }

  printf("%d\n", (int)ans.size());
  for (auto [a, b, c, d]: ans) {
    printf("%d %d %d %d\n", a, b, c, d);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
  return 0;
}
