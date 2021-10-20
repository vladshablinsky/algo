#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int INF = 1000000000;

//-------------------------------------
struct tree {
  vector<vector<int>> g;
  vector<int> tin;
  vector<int> tout;
  vector<int> depth;
  // p(a, i) vertex if we go from a 2 ** i steps up
  vector<vector<int>> up;
  int timer{0};
  int l{0};
  int n;

  void input(int nn) {
    n = nn;
    g.resize(n);
    tin.resize(n);
    tout.resize(n);
    depth.resize(n);
    up.resize(n);
    while ((1 << l) < n) {
      ++l;
    }
    for (int i = 0; i < n; ++i) {
      up[i].resize(l);
    }

    int from, to;
    for (int i = 0; i < n - 1; ++i) {
      scanf("%d%d", &from, &to);
      --from;
      --to;
      g[from].push_back(to);
      g[to].push_back(from);
    }

    init_stuff(0);
  }

  bool is_parent(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
  }

  int lca(int a, int b) {
    if (is_parent(a, b)) return a;
    if (is_parent(b, a)) return b;

    // go up from a until p(a, 0) is a parent of b
    for (int j = l - 1; j >= 0; --j) {
      if (!is_parent(up[a][j], b)) {
        a = up[a][j];
      }
    }
    return up[a][0];
  }

  int dist(int a, int b) {
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
  }

private:
  // Roots parent is the root itself
  void dfs(int v, int p) {
    tin[v] = ++timer;
    for (int to: g[v]) {
      if (to != p) {
        depth[to] = depth[v] + 1;
        dfs(to, v);
        up[to][0] = v;
      }
    }
    tout[v] = ++timer;
  }

  void init_stuff(int root) {
    up[root][0] = root;
    depth[root] = 0;
    dfs(root, -1);

    for (int j = 1; j < l; ++j) {
      for (int from = 0; from < n; ++from) {
        up[from][j] = up[up[from][j - 1]][j - 1];
      }
    }
  }
};

//-------------------------------------
struct centroid_decomposition {
  // Centroids stuff
  tree& t;

  // centroid tree parents
  vector<int> parent;
  // centroid tree function of interest for vertices
  vector<int> f;
  vector<bool> used;
  vector<int> szs;

  // Init function of interest
  centroid_decomposition(tree& t)
    : t(t) {
    parent = vector<int>(t.n, -1);
    f = vector<int>(t.n, INF);
    used.resize(t.n, false);
    szs.resize(t.n, 0);
    dfs(0, -1, -1, t.n);
  }

  int dfs(int v, int p, int attach, int sz) {
    if (!sz) {
      return 0;
    }

    static set<pair<int, int>> removed_edges;

    int subtree_size = 1;
    // vector<pair<int, int>> tos;
    for (auto to: t.g[v]) {
      if (used[to] || to == p) {
        continue;
      }

      int to_sz = szs[to] = dfs(to, v, attach, sz);
      if (to_sz) {
        // tos.emplace_back(to, to_sz);
        subtree_size += to_sz;
      } else {
        return 0;
      }
    }

    // Found the centroid (v). Report split.
    if (int upsize = sz - subtree_size; upsize <= sz / 2) {
      parent[v] = attach;
      used[v] = true;
      for (auto to: t.g[v]) {
        if (!used[to] && to != p) {
          dfs(to, -1, v, szs[to]);
        }
      }

      dfs(p, -1, v, upsize);
      return 0;
    }

    return subtree_size;
  }

  void update(int a) {
    f[a] = 0;
    int b = a;
    while (b != -1) {
      f[b] = min(f[b], t.dist(a, b));
      b = parent[b];
    }
  }

  int query(int a) {
    int res = INF;
    int b = a;
    while (b != -1) {
      int dist = t.dist(a, b);
      res = min(res, f[b] + dist);
      b = parent[b];
    }
    return res;
  }
};
//-------------------------------------

void solve() {
  int n;
  int m;
  scanf("%d%d", &n, &m);

  tree t;
  t.input(n);

  centroid_decomposition cd(t);

  cd.update(0);

  for (int i = 0; i < m; ++i) {
    int query_id, v;
    scanf("%d%d", &query_id, &v);
    --v;
    if (query_id == 1) {
      cd.update(v);
    } else {
      printf("%d\n", cd.query(v));
    }
  }
}

int main() {
  solve();
}
