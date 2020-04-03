#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
long long sum_subtr[MAXN]; // sum of all vertices in subtree
int used[MAXN];
int a[MAXN];

vector<int> g[MAXN];
long long result = 0;

long long dfs1(int v) {
  long long ans = 0;
  used[v] = 1;
  sum_subtr[v] = a[v];
  for (auto to: g[v]) {
    if (used[to] != 1) {
      ans += dfs1(to);
      sum_subtr[v] += sum_subtr[to];
    }
  }
  ans += sum_subtr[v] - a[v];
  return ans;
}

void dfs2(int v, long long ans_for_parent, long long suptree_sum) {
  used[v] = 2;
  long long ans_for_v = ans_for_parent + suptree_sum - sum_subtr[v];
  result = max(result, ans_for_v);
  for (auto to: g[v]) {
    if (used[to] != 2) {
      dfs2(to, ans_for_v, suptree_sum + sum_subtr[v] - sum_subtr[to]);
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    --from; --to;
    g[from].push_back(to);
    g[to].push_back(from);
  }

  // root is 0
  long long ans_for_0 = dfs1(0);
  dfs2(0, ans_for_0 + sum_subtr[0], 0);
  cout << result << "\n";
  return 0;
}
