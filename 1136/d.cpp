#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXN = 300005;

unordered_set<int> g[MAXN];
int a[MAXN];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].insert(v);
  }

  int x = a[n - 1];
  int ans = 0;
  unordered_set<int> cur_need_swap_with;
  for (int i = n - 2; i >= 0; --i) {
    if (g[a[i]].count(x)) {
      int cnt = 0;
      for (auto &el: g[a[i]]) {
        if (cur_need_swap_with.count(el)) {
          ++cnt;
        }
      }
      if (cnt != cur_need_swap_with.size()) {
        cur_need_swap_with.insert(a[i]);
      } else {
        ++ans;
      }
    } else {
      cur_need_swap_with.insert(a[i]);
    }
  }
  cout << ans << "\n";
  return 0;
}
