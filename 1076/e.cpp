#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 300005;
long long result_for_v[MAXN];
bool used[MAXN];
vector<int> g[MAXN];
vector<pair<int, int>> queries_for_v[MAXN];
int n;

struct Node {
  long long sum;
  long long to_push;
  int length;
  Node(): sum(0), to_push(0), length(0) {}
} t[4 * MAXN];

void push_tree(int v) {
  if (t[v].to_push) {
    t[v].sum += t[v].to_push * t[v].length;
    if (t[v].length > 1) {
      t[v * 2].to_push += t[v].to_push;
      t[v * 2 + 1].to_push += t[v].to_push;
    }
    t[v].to_push = 0;
  }
}

void init_tree(int v, int tl, int tr) {
  if (tl == tr) {
    t[v].length = 1;
  } else {
    int tm = (tl + tr) / 2;
    init_tree(v * 2, tl, tm);
    init_tree(v * 2 + 1, tm + 1, tr);
    t[v].length = t[v * 2].length + t[v * 2 + 1].length;
  }
}

long long query_tree(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return 0;
  }
  push_tree(v);
  if (tl == l && tr == r) {
    return t[v].sum;
  } else {
    int tm = (tl + tr) / 2;
    return query_tree(v * 2, tl, tm, l, min(r, tm)) +
      query_tree(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
  }
}

void update_tree(int v, int tl, int tr, int l, int r, long long delta) {
  if (l > r) {
    return;
  }
  if (tl == tr) {
    t[v].sum += delta;
  } else if (tl == l && tr == r) {
    t[v].to_push += delta;
  } else {
    push_tree(v);
    int tm = (tl + tr) / 2;
    t[v].sum += (r - l + 1) * delta;
    update_tree(v * 2, tl, tm, l, min(tm, r), delta);
    update_tree(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, delta);
  }
}

void dfs(int v, int depth) {
  used[v] = true;
  for (auto q: queries_for_v[v]) {
    update_tree(1, 0, n, depth, min(depth + q.first, n), q.second);
  }
  result_for_v[v] = query_tree(1, 0, n, depth, depth);

  for (auto to: g[v]) {
    if (!used[to]) {
      dfs(to, depth + 1);
    }
  }

  for (auto q: queries_for_v[v]) {
    update_tree(1, 0, n, depth, min(depth + q.first, n), -q.second);
  }
}

int main() {
  int m;
  scanf("%d", &n);
  init_tree(1, 0, n);
  //debug_tree();

  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    int v, d, x;
    scanf("%d%d%d", &v, &d, &x);
    queries_for_v[v].push_back({d, x});
  }

  dfs(1, 0);
  for (int i = 1; i <= n; ++i) {
    cout << result_for_v[i] << " ";
  }
  cout << "\n";
  return 0;
}
