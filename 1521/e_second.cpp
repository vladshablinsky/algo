#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <deque>
#include <unordered_set>

using namespace std;

const int MAXN = 100005;
unordered_set<int> g[MAXN];
vector<pair<int, int>> removed_edges;
vector<deque<int>> bambs;

int deg(int v) {
  return g[v].size();
}

void dfs(int v, int p, deque<int>& bamb, bool push_right) {
  // cout << "dfs: " << v << endl;
  // cout << "populate ";
  // for (auto el: bamb) {
  //   cout << el << ", ";
  // }
  // cout << "with " << v << " to the ";
  if (push_right) {
    // cout << "right\n";
    bamb.push_back(v);
  } else {
    // cout << "left\n";
    bamb.push_front(v);
  }

  deque<int> children;
  for (auto to: g[v]) {
    if (to != p) {
      if (deg(to) > 2) {
        children.push_front(to);
      } else {
        children.push_back(to);
      }
    }
  }

  while (deg(v) > 2) {
    int child = children.front();
    children.pop_front();
    // cout << "deg " << v << " > 2 " << ", split with " << child << endl;
    removed_edges.push_back({child, v});
    g[v].erase(child);
    g[child].erase(v);

    deque<int> subbamb;
    dfs(child, v, subbamb, false);
    bambs.push_back(std::move(subbamb));
  }

  if (children.size()) {
    int child = children.front();
    children.pop_front();
    dfs(child, v, bamb, false | push_right);
  }

  if (children.size()) {
    int child = children.front();
    children.pop_front();
    dfs(child, v, bamb, true);
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    g[i].clear();
  }

  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    g[from].insert(to);
    g[to].insert(from);
  }
  removed_edges.clear();
  bambs.clear();

  // cout << "EDGES:\n";
  // for (int i = 1; i <= n; ++i) {
  //   for (auto to: g[i]) {
  //     cout << i << "-"<<to << endl;
  //   }
  // }
  // cout << "END EDGES:\n";

  deque<int> dq;
  dfs(1, -1, dq, false);
  bambs.push_back(std::move(dq));

  // cout << "bambs:\n";
  // for (auto bamb: bambs) {
  //   for (auto v: bamb) {
  //     cout << v << " ";
  //   }
  //   cout << "\n === \n";
  // }

  // cout << "removed edges\n";
  printf("%d\n", (int)removed_edges.size());
  for (int i = 0; i < removed_edges.size(); ++i) {
    auto [r_a, r_b] = removed_edges[i];
    int i_a = bambs[i].back();
    int i_b = bambs[i + 1].front();
    printf("%d %d %d %d\n", r_a, r_b, i_a, i_b);
  }
  // for(auto [from, to]: removed_edges) {
  //   cout << from << " " << to << endl;
  // }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
  return 0;
}
