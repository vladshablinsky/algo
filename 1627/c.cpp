#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 100005;

// (to, index of the edge)
vector<pair<int, int>> g[MAXN];
int weights[MAXN];

void init(int n) {
  for (int i = 0; i < n; ++i) {
    g[i].clear();
  }
}

void dfs(int v, int income=-1, int p=-1) {
  int outcome;
  if (income == -1) {
    outcome = 2;
  } else {
    outcome = income ^ 1;
  }

  for (auto [to, i]: g[v]) {
    if (to != p) {
      weights[i] = outcome;
      dfs(to, outcome, v);
      outcome ^= 1;
    }
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  init(n);

  int from, to;
  bool overpowered = false;
  for (int i = 0; i < n - 1; ++i) {
    scanf("%d%d", &from, &to);
    --from;
    --to;
    g[from].push_back({to, i});
    g[to].push_back({from ,i});

    overpowered |= g[from].size() >= 3;
    overpowered |= g[to].size() >= 3;
  }

  if (overpowered) {
    printf("-1\n");
  } else {
    dfs(0, 2);
    for (int i = 0; i < n - 1; ++i) {
      printf("%d ", weights[i]);
    }
    printf("\n");
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
