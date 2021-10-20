#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100005;
int a[MAXN];
vector<int> g[MAXN];

int same_subtree_cnt;
int global_xor;
bool any_same_as_subtree;

void init(int n) {
  same_subtree_cnt = 0;
  any_same_as_subtree = false;

  for (int i = 0; i < n; ++i) {
    g[i].clear();
  }
}

int dfs(int v, int p) {
  int v_subtree_xor = 0;
  for (auto to: g[v]) {
    if (to != p) {
      int to_subtree_xor = dfs(to, v);
      v_subtree_xor ^= to_subtree_xor;
    }
  }
  v_subtree_xor ^= a[v];

  if (v_subtree_xor == global_xor && (global_xor ^ v_subtree_xor == global_xor)) {
    // cout << "at " << v << " ok " << endl;
    same_subtree_cnt++;
  }

  // Primarily for global xor = 0
  // root does not count!
  if (v && v_subtree_xor == global_xor ^ v_subtree_xor) {
    any_same_as_subtree = true;
  }
  return v_subtree_xor;
}

bool solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  init(n);

  int all_xor = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    all_xor ^= a[i];
  }

  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    --from;
    --to;
    g[from].push_back(to);
    g[to].push_back(from);
  }


  // two cases here. Either xor zero, or X
  global_xor = all_xor;
  dfs(0, -1);

  if (all_xor) {
    return k > 2 && same_subtree_cnt >= 2;
  } else {
    return any_same_as_subtree;
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    if (solve()) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
}
