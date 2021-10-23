#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100005;
int a[MAXN];
vector<int> g[MAXN];
int target_xor = 0;

void init(int n) {
  target_xor = 0;
  for (int i = 0; i < n; ++i) {
    g[i].clear();
  }
}

// return xor of subtree and flag if one of the subtrees had xor a
// we're seeking for a vertex where two or more children with a flag returned
pair<int, bool> dfs(int v, int p, bool& ans) {
  int cnt_target_xor = 0;
  int whole_subtree_xor = a[v];

  int cnt_child = 0;
  for (auto to: g[v]) {
    if (to == p) {
      continue;
    }
    ++cnt_child;

    auto [to_xor, to_found_target] = dfs(to, v, ans);
    if (ans) {
      return {};
    }

    cnt_target_xor += to_found_target;
    whole_subtree_xor ^= to_xor;
  }

  int uptree_xor = whole_subtree_xor ^ target_xor;
  if (uptree_xor == target_xor && cnt_target_xor) {
    ans = true;
    return {};
  }

  if (cnt_target_xor > 1) {
    ans = true;
    return {};
  }

  // cout << "dfs: " << v << endl;
  cnt_target_xor |= (whole_subtree_xor == target_xor);
  // cout << "returning: " << whole_subtree_xor << ", " << cnt_target_xor << endl;
  return {whole_subtree_xor, cnt_target_xor};
}

bool solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  init(n);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    target_xor ^= a[i];
  }

  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    --from;
    --to;
    g[from].push_back(to);
    g[to].push_back(from);
  }

  // cout << "TARGET: " << target_xor << endl;

  if (target_xor) {
    bool ans = false;
    dfs(0, -1, ans);
    return k > 2 && ans;
  } else {
    return true;
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
