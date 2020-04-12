#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int INF = 1e9;
const int MAXN = 100005;
const int MAXP = 18;

vector<int> g[MAXN];
int tin[MAXN];
int tout[MAXN];
int depth[MAXN];
int p[MAXN][MAXP];
bool used[MAXN];
int timer = 0;

bool is_upper(int a, int b) {
  return tin[a] <= tin[b] && tout[a] >= tout[b];
}

void dfs(int v, int cur_depth) {
  tin[v] = timer++;
  used[v] = true;
  depth[v] = cur_depth;
  for (auto to: g[v]) {
    if (!used[to]) {
      p[to][0] = v;
      dfs(to, cur_depth + 1);
    }
  }
  tout[v] = timer++;
}

void init_p(int n) {
  dfs(1, 0);
  p[1][0] = 1;
  for (int j = 1; j < MAXP; ++j) {
    p[1][j] = 1;
    for (int i = 1; i <= n; ++i) {
      p[i][j] = p[p[i][j - 1]][j - 1];
    }
  }
}

int lca(int a, int b) {
  if (a == -1 || b == -1) {
    return max(a, b);
  }
  if (is_upper(a, b)) return a;
  if (is_upper(b, a)) return b;
  for (int i = MAXP - 1; i >= 0; --i) {
    if (!is_upper(p[a][i], b)) {
      a = p[a][i];
    }
  }
  return p[a][0];
}

struct Node {
  vector<int> lo_and_hi;
} t[4 * MAXN];

void combine(const vector<int> &v1, const vector<int> &v2, vector<int> &target) {
  static auto cmp = [](int x, int y) {
    return tin[x] < tin[y];
  };

  vector<int> v(v1.begin(), v1.end());
  v.insert(v.end(), v2.begin(), v2.end());

  sort(v.begin(), v.end(), cmp);
  if (v.size() <= 4) {
    target = std::move(v);
  } else {
    target.clear();
    target.insert(target.end(), v.begin(), v.begin() + 2);
    target.insert(target.end(), v.end() - 2, v.end());
  }
}

void init_t(int v, int tl, int tr) {
  if (tl == tr) {
    t[v].lo_and_hi.push_back(tl);
  } else {
    int tm = (tl + tr) / 2;
    init_t(v * 2, tl, tm);
    init_t(v * 2 + 1, tm + 1, tr);
    combine(t[v * 2].lo_and_hi, t[v * 2 + 1].lo_and_hi, t[v].lo_and_hi);
  }
}

vector<int> query(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return {};
  }
  if (tl == l && tr == r) {
    return t[v].lo_and_hi;
  } else {
    int tm = (tl + tr) / 2;
    vector<int> ans;
    combine(query(v * 2, tl, tm, l, min(tm, r)),
        query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r), ans);
    return ans;
  }
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 2; i <= n; ++i) {
    int p_i;
    scanf("%d", &p_i);
    g[p_i].push_back(i);
  }
  init_p(n);
  init_t(1, 1, n);

  for (int i = 0; i < q; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    auto res = query(1, 1, n, l, r);
    int v_to_remove = res.back();
    int best_depth = -1;
    int cur_lca;
    // for (auto el: res) {
    //   cout << el << " ";
    // }
    // cout << endl;
    if (depth[cur_lca = lca(*next(res.begin()), *res.rbegin())] > best_depth) {
      best_depth = depth[cur_lca];
      v_to_remove = *res.begin();
    }
    if (depth[cur_lca = lca(*res.begin(), *next(res.rbegin()))] > best_depth) {
      best_depth = depth[cur_lca];
      v_to_remove = *res.rbegin();
    }
    if (res.size() > 2 && depth[cur_lca = lca(*res.begin(), *res.rbegin())] > best_depth) {
      best_depth = depth[cur_lca];
      v_to_remove = *next(res.begin());
    }

    printf("%d %d\n", v_to_remove, best_depth);
  }
  return 0;

  return 0;
}
