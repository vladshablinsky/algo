#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int kMaxN = 200005;
constexpr int kInf = 1000000001;

vector<int> g_out[kMaxN];
vector<int> g_in[kMaxN];

int a[kMaxN];
int color[kMaxN];
int d[kMaxN];
int timer = 0;
int max_len = 0;

void init(int n) {
  for (int i = 0; i < n; ++i) {
    color[i] = 0;
    d[i] = 0;
  }
  max_len = 0;
}

void dfs(int v, int decline_greater, bool& has_loop) {
  color[v] = 1;

  d[v] = 0;
  for (auto to: g_out[v]) {
    if (a[to] > decline_greater) {
      continue;
    }

    if (!color[to]) {
      dfs(to, decline_greater, has_loop);
    } else if (color[to] == 1) {
      has_loop = true;
    }

    d[v] = max(d[to] + 1, d[v]);
  }

  color[v] = 2;
  max_len = max(max_len, d[v]);
}

bool check(int n, int decline_greater, long long len) {
  bool has_loop = false;
  bool no_dfs = true;
  bool any_vertex = false;
  init(n);
  for (int i = 0; i < n; ++i) {
    if (a[i] > decline_greater) {
      continue;
    }

    any_vertex = true;

    if (!color[i]) {
      bool any_income = false;
      for (auto from: g_in[i]) {
        any_income |= (a[from] <= decline_greater);
      }

      if (!any_income) {
        no_dfs = false;
        dfs(i, decline_greater, has_loop);
      }
    }
  }

  if (!any_vertex) {
    return false;
  } else if (has_loop || no_dfs) {
    return true;
  } else { // DAG
    return len <= max_len;
  }
}

int main() {
  int n, m;
  long long k;
  scanf("%d%d%lld", &n, &m, &k);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  for (int i = 0; i < m; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    g_out[from - 1].push_back(to - 1);
    g_in[to - 1].push_back(from - 1);
  }

  // binsearch
  int l = 1;
  int r = 10;
  int ans = kInf;
  while (l <= r) {
    int m = (l + r) / 2;
    if (check(n, m, k - 1)) {
      ans = min(ans, m);
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  if (ans == kInf) {
    printf("-1\n");
  } else {
    printf("%d\n", ans);
  }
}
