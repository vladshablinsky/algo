#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1e9;

struct Tree {
  vector<int> tin;
  vector<int> tout;
  vector<int> depth;
  vector<vector<int>> g;
  vector<vector<int>> up;
  int n;
  int l{0};
  int timer{0};

  Tree(int n) : n(n) {
    g.resize(n);
    tin.resize(n);
    tout.resize(n);
    depth.resize(n);

    while ((1 << l) < n) {
      ++l;
    }
    up.resize(n);
    for (int i = 0; i < n; ++i) {
      up[i].resize(l);
    }
  }

  void input() {
    int v, u;
    for (int i = 0; i < n - 1; ++i) {
      scanf("%d%d", &u, &v);
      --u;
      --v;
      g[u].push_back(v);
      g[v].push_back(u);
    }

    init();
  }

  bool is_upper(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
  }

  int dist(int a, int b) {
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
  }

  int lca(int a, int b) {
    if (is_upper(a, b)) {
      return a;
    }
    if (is_upper(b, a)) {
      return b;
    }

    for (int i = l - 1; i >= 0; --i) {
      if (!is_upper(up[a][i], b)) {
        a = up[a][i];
      }
    }
    return up[a][0];
  }

private:
  void init() {
    depth[0] = 0;
    up[0][0] = 0;
    dfs(0, -1);

    for (int i = 1; i < l; ++i) {
      for (int v = 0; v < n; ++v) {
        up[v][i] = up[up[v][i - 1]][i - 1];
      }
    }
  }

  void dfs(int v, int p) {
    tin[v] = timer++;

    for (auto to: g[v]) {
      if (to != p) {
        depth[to] = depth[v] + 1;
        up[to][0] = v;
        dfs(to, v);
      }
    }

    tout[v] = timer++;
  }
};

struct CDOT {
  Tree& t;

  vector<int> par;
  vector<int> f;
  vector<int> szs;
  vector<bool> used; // mark nodes as centroids already processed
  int n;

  CDOT(Tree& t)
    : t(t)
  {
    n = t.n;
    par.resize(n, -1);
    szs.resize(n, 0);
    used.resize(n, false);
    f.resize(n, INF);

    dfs(0, -1, -1, n);
  }

  void update(int a) {
    f[a] = 0;
    int b = a;
    while (b != -1) {
      f[b] = min(f[b], t.dist(a, b));
      b = par[b];
    }
  }

  int query(int a) {
    int res = INF;
    int b = a;
    while (b != -1) {
      res = min(res, f[b] + t.dist(a, b));
      b = par[b];
    }
    return res;
  }

private:
  // returns zero if centroid split occured. Now it have been processed
  // in a detached dfs;
  int dfs(int v, int p, int attach, int sz) {
    // NOTE: important here
    if (!sz) {
      return 0;
    }

    int subtrees_sz = 1; // self

    for (auto to: t.g[v]) {
      if (used[to] || to == p) {
        continue;
      }

      auto to_sz = szs[to] = dfs(to, v, attach, sz);
      if (!to_sz) {
        return 0;
      }
      subtrees_sz += to_sz;
    }

    // uptree sz.
    // v is a centroid!
    if (sz - subtrees_sz <= sz / 2) {
      used[v] = true;
      par[v] = attach;

      for (auto to: t.g[v]) {
        if (!used[to] && to != p) {
          dfs(to, -1, v, szs[to]);
        }
      }

      if (p != -1) {
        dfs(p, -1, v, sz - subtrees_sz);
      }
      return 0;
    }

    return subtrees_sz;
  }
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);

  Tree t(n);
  t.input();

  CDOT cd(t);
  cd.update(0);
  for (int i = 0; i < m; ++i) {
    int q_id, v;
    scanf("%d%d", &q_id, &v);
    --v;
    if (q_id == 1) {
      cd.update(v);
    } else {
      printf("%d\n", cd.query(v));
    }
  }
}
