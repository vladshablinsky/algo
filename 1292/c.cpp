#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 3005;

vector<int> g[MAXN];
int tree_size[MAXN];

int ans_1;
int ans_2;
int ans_right;
int occupied_size;
int free_size;

void dfs_tree_size(int v, int p) {
  tree_size[v] = 1;
  for (auto to: g[v]) {
    if (to != p) {
      dfs_tree_size(to, v);
      tree_size[v] += tree_size[to];
    }
  }
}

void dfs_left(
    int v,
    int p,
    int incoming_edge,
    int up_1,
    int up_2,
    int occupied_up
) {

  cout << "dfs_left: " << incoming_edge << " " << up_1 << endl;

  for (auto to: g[v]) {
    if (to != p) {
      int to_up_1 = up_1;
      int to_up_2 = up_2;
      if (incoming_edge) {
        to_up_1 += (incoming_edge + 1) * (tree_size[v] - tree_size[to]);
        to_up_2 += (incoming_edge + 2) * (tree_size[v] - tree_size[to]);
      }
      dfs_left(
        to,
        v,
        incoming_edge + 1,
        to_up_1,
        to_up_2,
        occupied_up + (tree_size[v] - tree_size[to]) * (!!incoming_edge)
      );
    }
  }

  // Skip this step if incoming_edge is zero, since we claim we always take edge 1.
  if (incoming_edge && up_1 + tree_size[v] * (incoming_edge + 1) > ans_1) {
    ans_1 = up_1 + tree_size[v] * (incoming_edge + 1);
    ans_2 = up_2 + tree_size[v] * (incoming_edge + 2);
    occupied_size = occupied_up + tree_size[v];
  }
}

void dfs_right(int v, int p, int up, int incoming_edge) {
  for (auto to: g[v]) {
    if (to != p) {
      dfs_right(
        to,
        v,
        up + (incoming_edge + 1) * (tree_size[v] - tree_size[to]),
        incoming_edge + 1
      );
    }
  }

  cout << "ans for vertex " << v << ", tree_size: " << tree_size[v] << endl;
  int cur_ans = 0;
  int left_size = free_size + occupied_size;

  // mex = incoming_edge + 1
  // All pathes having this edge and edges 0...incoming_edge
  // excluding pathes having incoming_edge + 2
  cur_ans += tree_size[v] * free_size * (incoming_edge + 1);
  cout << "add mex = " << incoming_edge + 1 << " (start here, end in free): " << tree_size[v] * free_size * (incoming_edge + 1) << endl;

  // mex = {incoming_edge + 2, incoming_edge + 3, ...}
  // All pathes having this edge and edges 0...incoming_edge both with
  // edges {incoming_edge + 2 ...} on the Left side
  cur_ans += (ans_1 + (ans_2 - ans_1) * incoming_edge) * tree_size[v];
  cout << "add mex = " << incoming_edge + 2 << "... and greater (start here, end in L chain) " << (ans_1 + (ans_2 - ans_1) * incoming_edge) * tree_size[v] << endl;

  // mex = {1, 2, ..., incoming_edge + 1}
  // All pathes with mex = 1, 2, ...
  // They begins somewhere above and end in any edge in L.
  // Exception is when incoming_edge is 0. This case is calculated above.
  if (incoming_edge) {
    cur_ans += up * (left_size);
    cout << "add upper mex={1, 2, ...} (start up, end anywhere in left) " << up * (left_size) << endl;
  }

  ans_right = max(ans_right, cur_ans);
}

void solve_for_edge(int l, int r) {
  cout << "solving for " << l << " " << r << endl;
  cout << "----------------------------------\n";
  ans_1 = 0;
  ans_2 = 0;
  occupied_size = 0;
  dfs_tree_size(l, r);
  dfs_left(l, r, 0, 0, 0, 0);
  dfs_tree_size(r, l);
  free_size = tree_size[l] - occupied_size;
  cout << "ans_1: " << ans_1 << ", ans_2 " << ans_2 << ", occupied_size: " << occupied_size << ", free_size: " << free_size << ", occupied: " << occupied_size << endl;

  dfs_right(r, l, 0, 0);
  cout << "now ans: "<<  ans_right << endl;
}

int main() {
  int n;
  scanf("%d", &n);
  vector<pair<int, int>> edges(n - 1);
  for (auto& [from, to]: edges) {
    scanf("%d%d", &from, &to);
    g[from].push_back(to);
    g[to].push_back(from);
  }

  solve_for_edge(4, 7);
  cout << ans_right << "\n";
  return 0;

  int result = 0;
  for (const auto& [from, to]: edges) {
    solve_for_edge(from, to);
    solve_for_edge(to, from);
  }

  cout << ans_right << "\n";
  return 0;
}
