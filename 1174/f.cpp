#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 2e5 + 2;

vector<int> g[MAX_N];
bool used[MAX_N];
bool filtered[MAX_N];
int subtree_size[MAX_N];
int best_child[MAX_N];
int best_leaf[MAX_N];
int p[MAX_N];
int n;

int depth_subtree(int v, int cur_depth, int target_depth) {
  // cout << "depth_subtree " << v << ", " << cur_depth << ", " << target_depth << endl;
  int max_subtree_depth = 0;
  used[v] = true;
  for (auto to: g[v]) {
    if (!used[to]) {
      p[to] = v;
      max_subtree_depth = max(max_subtree_depth, depth_subtree(to, cur_depth + 1, target_depth - 1) + 1);
    }
  }

  // too deep
  if (target_depth < 0 || max_subtree_depth < target_depth) {
    filtered[v] = true;
    // cout << "filter out " << v << endl;
  }

  return max_subtree_depth;
}

int dfs(int v) {
  used[v] = true;
  if (filtered[v]) {
    return 0;
  }

  int cur_max_child_subtree_size = 0;
  for (auto to: g[v]) {
    if (!used[to]) {
      subtree_size[v] += dfs(to);
      if (subtree_size[to] > cur_max_child_subtree_size) {
        cur_max_child_subtree_size = subtree_size[to];
        best_leaf[v] = best_leaf[to];
        best_child[v] = to;
      }
    }
  }

  subtree_size[v]++;
  if (subtree_size[v] == 1) {
    best_leaf[v] = v;
    best_child[v] = v;
  }

  //cout << "Node: " << v << ", best_leaf: " << best_leaf[v]  << ", best_child: " << best_child[v]  << ", subtree_size: " << subtree_size[v] << endl;
  return subtree_size[v];
}

int query_second(int v) {
  int res;
  cout << "s " << v + 1 << "\n";
  cin >> res;
  return res - 1;
}

int query_distance(int v) {
  int res;
  cout << "d " << v + 1 << "\n";
  cin >> res;
  return res;
}

void query_finialize(int v) {
  cout << "! " << v + 1 << "\n";
  cout.flush();
}

void clear_used() {
  for (int i = 0; i < MAX_N; ++i) {
    used[i] = false;
  }
}

int main() {
  cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    cin >> from >> to;
    --from;
    --to;
    g[from].push_back(to);
    g[to].push_back(from);
  }

  int distance = query_distance(0);
  depth_subtree(0, 0, distance);
  clear_used();
  dfs(0);

  int cur_node = 0;
  for (;;) {
    if (distance == 0) {
      query_finialize(cur_node);
      return 0;
    }
    int child = best_child[cur_node];
    int leaf = best_leaf[child];
    // cout << "cur_node: " << cur_node << ", child: " << child << ", leaf: " << leaf << endl;
    int d_from_leaf_to_x = query_distance(leaf);
    if (d_from_leaf_to_x == 0) {
      query_finialize(leaf);
      return 0;
    } else if (d_from_leaf_to_x == distance - 1) {
      cur_node = query_second(child);
      distance -= 2;
    } else {
      cur_node = leaf;
      for (int i = 0; i < d_from_leaf_to_x / 2; ++i) {
        cur_node = p[cur_node];
      }
      cur_node = query_second(cur_node);
      distance = d_from_leaf_to_x / 2 - 1;
    }
    // cout << "cur_node now " << cur_node << ", dist: " << distance << endl;
  }
  return 0;
}
