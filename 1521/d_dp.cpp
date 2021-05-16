#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <deque>

using namespace std;

const int MAXN = 200005;
const int INF = 1e9;
vector<int> g[MAXN];
int f_split[MAXN];
int f_take[MAXN];
vector<int> p_split[MAXN];
vector<int> p_take[MAXN];
vector<deque<int>> chains;
vector<pair<int, int>> removed_edges;

struct two_min {
  // first is always smaller
  pair<int, int> el[2];
  int size{};

  void add(const pair<int, int>& x) {
    if (size == 2) {
      if (x <= el[0]) {
        swap(el[0], el[1]);
        el[0] = x;
      } else if (x <= el[1]) {
        el[1] = x;
      }
    } else {
      el[size++] = x;
      if (size == 2 && el[0] > el[1]) {
        swap(el[0], el[1]);
      }
    }
  }

  pair<int, int> min_1() {
    return el[0];
  }

  pair<int, int> min_2() {
    return el[1];
  }
};

void dfs(int v, int p) {
  int cnt_sons = 0;
  two_min min_takes;
  int sum_split = 0;
  for (auto to: g[v]) {
    if (to != p) {
      ++cnt_sons;
      dfs(to, v);
      min_takes.add({-f_split[to] + f_take[to], to});
      sum_split += f_split[to];
    }
  }

  //cout << "dfs " << v << endl;
  //cout << "cnt sons: " << cnt_sons << endl;
  //cout << "min takes: {";
  //for (int i = 0; i < min_takes.size; ++i) {
  //  cout << "{" << min_takes.el[0].first << ", " << min_takes.el[0].second <<  "}";
  //}
  //cout << "}\n";

  if (!cnt_sons) {
    f_split[v] = 0;
    f_take[v] = 0;
  } else {
    auto min_1 = min_takes.min_1();
    int path_start_v = sum_split + min_1.first + cnt_sons - 1;
    int split_all = sum_split + cnt_sons;
    if (min_takes.size == 1) {
      if (path_start_v < split_all) {
        f_take[v] = path_start_v;
        p_take[v] = {min_1.second}; // meaning edge (v,min_1.second) taken
      } else {
        f_take[v] = split_all;
      }

      // same since only one child
      f_split[v] = f_take[v];
      p_split[v] = p_take[v];
    } else {
      auto min_2 = min_takes.min_2();
      int path_through_v = sum_split + min_1.first + min_2.first + (cnt_sons - 2);

      // Just set initial value.
      // Split is always an option in case we take parent.
      f_take[v] = split_all;
      f_split[v] = split_all;

      if (path_start_v < split_all) {
        f_split[v] = path_start_v;
        p_split[v] = {min_1.second};

        // Better fit for take
        f_take[v] = path_start_v;
        p_take[v] = {min_1.second};
      }

      if (path_through_v < min(path_start_v, split_all)) {
        // Not an option for f_take, however might be a better fit for split.
        f_split[v] = path_through_v;
        p_split[v] = {min_1.second, min_2.second};
      }
    }
  }
}

// split indicating whether the parent was is same chain or not.
// split = true means there was a split up, so we use split dp-s
void split_from_root(int root, int parent, bool split, deque<int>& chain, bool push_right) {
  if (push_right) {
    chain.push_back(root);
  } else {
    chain.push_front(root);
  }

  auto& dp = split ? f_split[root] : f_take[root];
  auto& p = split ? p_split[root] : p_take[root];

  vector<int> copy_g_v(g[root].begin(), g[root].end());
  bool push_left = false;
  for (auto to: copy_g_v) {
    if (to == parent) {
      continue;
    }

    // Optimal split does not take (root, to) edge, thus use split=true
    if (find(p.begin(), p.end(), to) == p.end()) {
      removed_edges.push_back({root, to});
      deque<int> subchain;
      split_from_root(to, root, true, subchain, false);
      chains.push_back(std::move(subchain));
    } else {
      split_from_root(to, root, false, chain, push_left | push_right);
      push_left = true;
    }
  }
}

void solve() {
  int n;
  scanf("%d", &n);

  chains.clear();
  for (int i = 1; i <= n; ++i) {
    p_split[i].clear();
    p_take[i].clear();
    removed_edges.clear();
    g[i].clear();
  }

  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    g[from].push_back(to);
    g[to].push_back(from);
  }

  {
    dfs(1, -1);
    deque<int> chain;
    split_from_root(1, -1, true, chain, false);
    chains.push_back(std::move(chain));
  }

  // {
  //   cout << "chains: \n";
  //   for (auto chain: chains) {
  //     for (auto el: chain) {
  //       cout << el << " ";
  //     }
  //     cout << endl;
  //   }
  // }

  // {
  //   cout << "dp debug: \n";
  //   for (int i = 1; i <= n; ++i) {
  //     cout << i << ", take: " << f_take[i] << ", split: " << f_split[i] << endl;
  //   }
  // }

  printf("%d\n", (int)removed_edges.size());
  for (int i = 0; i < removed_edges.size(); ++i) {
    auto [r_a, r_b] = removed_edges[i];
    int i_a = chains[i].back();
    int i_b = chains[i + 1].front();
    printf("%d %d %d %d\n", r_a, r_b, i_a, i_b);
  }

}

int main() {
  int t;
  scanf("%d\n", &t);
  while (t--) {
    solve();
  }

  return 0;
}

