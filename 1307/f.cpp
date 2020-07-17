#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
const int POW = 19;
const int INF = 1e9;

int n, k, r;
vector<int> g[MAXN];
// task-specific
bool is_station[MAXN];
int fuel[MAXN];

// for lca
int tin[MAXN];
int tout[MAXN];
int up[MAXN][POW];
int depth[MAXN];
int timer = 0;

// for hld
vector<vector<int>> hld_pathes;

// for segment tree hld
int subtree_size[MAXN];
int mapping[MAXN];  // maps v to segment tree vertex
int backmapping[MAXN]; // maps segment tree vertex to vertex
int v_to_path_id[MAXN];


// segment tree lives here
int t[4 * MAXN];

int dfs(int v, int p, int upper_station=-1) {
  up[v][0] = p;
  subtree_size[v] = 1;

  tin[v] = timer++;
  depth[v] = depth[p] + 1;
  if (is_station[v]) {
    upper_station = v;
  }

  if (upper_station != -1) {
    fuel[v] = k - (depth[v] - depth[upper_station]);
  } else {
    fuel[v] = -INF;
  }

  for (auto to: g[v]) {
    if (to != p) {
      fuel[v] = max(fuel[v], dfs(to, v, upper_station) - 1);
      subtree_size[v] += subtree_size[to];
    }
  }

  for (int j = 1; j < POW; ++j) {
    up[v][j] = up[up[v][j - 1]][j - 1];
  }
  tout[v] = timer++;
  return fuel[v];
}

bool is_heavy(int from, int to) {
  return subtree_size[to] > (subtree_size[from] - 1) / 2;
}

// vertex-hld
void hld_dfs(int v, int p, int path_id=-1) {
  if (path_id == -1) {
    path_id = 0;
    hld_pathes.push_back(vector<int>());
  }
  hld_pathes[path_id].push_back(v);
  v_to_path_id[v] = path_id;

  for (auto to: g[v]) {
    if (to != p) {
      if (!is_heavy(v, to)) {
        hld_pathes.push_back(vector<int>());
        hld_dfs(to, v, hld_pathes.size() - 1);
      } else {
        hld_dfs(to, v, path_id);
      }
    }
  }
}

void make_mapping_from_hld_pathes() {
  int cur_v = 1;
  for (auto &path: hld_pathes) {
    for (auto v: path) {
      mapping[v] = cur_v++;
      backmapping[mapping[v]] = v;
    }
  }
}

bool is_upper(int a, int b) {
  return tin[a] <= tin[b] && tout[b] <= tout[a];
}

int lca(int a, int b) {
  if (is_upper(a, b)) {
    return a;
  }
  if (is_upper(b, a)) {
    return b;
  }

  for (int j = POW - 1; j >= 0; --j) {
    if (!is_upper(up[a][j], b)) {
      a = up[a][j];
    }
  }
  return up[a][0];
}

void init_tree(int v, int tl, int tr) {
  if (tl == tr) {
    t[v] = fuel[backmapping[tl]];
  } else {
    int tm = (tl + tr) / 2;
    init_tree(v * 2, tl, tm);
    init_tree(v * 2 + 1, tm + 1, tr);
    t[v] = min(t[v * 2], t[v * 2 + 1]);
  }
}

int query(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return INF;
  }
  if (tl == tr) {
    return t[v];
  } else {
    int tm = (tl + tr) / 2;
    return min(
      query(v * 2, tl, tm, l, min(r, tm)),
      query(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r)
    );
  }
}

int query_path_mapped(int from, int to) {
  return query(1, 0, n, from, to);
}

// NOTE: a must be deeper than lca_ab;
int query_path_upper(int a, int lca_ab) {
  int lca_ab_path_id = v_to_path_id[lca_ab];
  int cur_min = INF;

  do {
    int a_path_id = v_to_path_id[a];
    int mapped_path_begin = mapping[hld_pathes[a_path_id].front()];

    if (a_path_id == lca_ab_path_id) {
      cur_min = min(cur_min, query_path_mapped(mapping[lca_ab], mapping[a]));
      break;
    } else {
      cur_min = min(cur_min, query_path_mapped(mapped_path_begin, mapping[a]));
    }
    if (a == up[a][0]) {
      break;
    }
    a = up[a][0];
  } while (a != lca_ab);
  return cur_min;
}

void solve(int from, int to) {
  int lca_ft = lca(from, to);
  int path_length = depth[from] + depth[to] - 2 * depth[lca_ft];
  if (path_length <= k) {
    printf("YES\n");
  } else {
    int min_on_path = min(query_path_upper(from, lca_ft), query_path_upper(to, lca_ft));
    if (min_on_path < 0) {
      printf("NO\n");
    } else {
      printf("YES\n");
    }
  }
}

void init_everything() {
  dfs(1, 1);
  hld_dfs(1, 1);
  make_mapping_from_hld_pathes();
  init_tree(1, 0, n);
}

int main() {
  scanf("%d%d%d", &n, &k, &r);

  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    g[from].push_back(to);
    g[to].push_back(from);
  }

  for (int i = 0; i < r; ++i) {
    int station_id;
    scanf("%d", &station_id);
    is_station[station_id] = true;
  }

  init_everything();

  for (auto &path: hld_pathes) {
    for (auto &v: path) {
      cout << v << " -> ";
    }
    cout << endl;
  }

  int v;
  scanf("%d", &v);
  for (int i = 0; i < v; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    solve(from, to);
  }
  return 0;
}
