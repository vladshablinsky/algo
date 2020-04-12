#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

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

// {lca_no_removed, [{lca_with_one_removed, removed_v},...]}
pair<int, vector<pair<int, int>>> t[4 * MAXN]; // segment tree

void combine_subtr(int &best_depth_with_kicked, vector<pair<int, int>> &kicked,
    vector<pair<int, int>> &removed_in_one_subtree, int other_subtree_lca) {


  for (auto &el: removed_in_one_subtree) {
    int cur_lca = lca(el.first, other_subtree_lca);
    //cout << "try to kick " << el.second << ",lca: " << el.first << ", other_sub_lca: "<< other_subtree_lca << ", res: " << cur_lca << endl;
    if (depth[cur_lca] > best_depth_with_kicked) {
      kicked.clear();
      best_depth_with_kicked = depth[cur_lca];
      kicked.push_back({cur_lca, el.second});
    }
  }
}

void init_tree(int v, int tl, int tr) {
  if (tl == tr) {
    t[v].first = tl;
    t[v].second.push_back({-1, tl});
  } else {
    int tm = (tl + tr) / 2;
    init_tree(v * 2, tl, tm);
    init_tree(v * 2 + 1, tm + 1, tr);

    t[v].first = lca(t[v * 2].first, t[v * 2 + 1].first);

    if (tl + 1 == tr) {
      t[v].second.push_back({tl, tr});
      t[v].second.push_back({tr, tl});
      if (depth[tl] < depth[tr]) {
        swap(t[v].second[0], t[v].second[1]);
      }
    } else {
      int best_with_kicked_l = -1;
      int best_with_kicked_r = -1;
      vector<pair<int, int>> kicked_v_l, kicked_v_r;
      combine_subtr(best_with_kicked_l, kicked_v_l, t[v * 2].second, t[v * 2 + 1].first);
      combine_subtr(best_with_kicked_r, kicked_v_r, t[v * 2 + 1].second, t[v * 2].first);

      //cout << tl << "..." << tr << endl;
      //cout << "best_with_kicked_l: " << best_with_kicked_l << endl;
      //cout << "best_with_kicked_r: " << best_with_kicked_r << endl;
      if (best_with_kicked_l > best_with_kicked_r) {
        t[v].second = std::move(kicked_v_l);
      } else {
        t[v].second = std::move(kicked_v_r);
      }
    }
  }
}

pair<int, vector<pair<int, int>>> query(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return {-1, vector<pair<int, int>>()};
  }
  if (tl == l && tr == r) {
    return t[v];
  } else {
    int tm = (tl + tr) / 2;
    auto res_l = query(v * 2, tl, tm, l, min(r, tm));
    auto res_r = query(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r);
    if (res_l.second.empty()) {
      return res_r;
    } else if (res_r.second.empty()) {
      return res_l;
    }

    pair<int, vector<pair<int, int>>> ans;
    ans.first = lca(res_l.first, res_r.first);


    if (tl + 1 == tr) {
      ans.second.push_back({tl, tr});
      ans.second.push_back({tr, tl});
      if (depth[tl] < depth[tr]) {
        swap(ans.second[0], ans.second[1]);
      }
    } else {
      int best_with_kicked_l = -1;
      int best_with_kicked_r = -1;
      vector<pair<int, int>> kicked_v_l, kicked_v_r;
      combine_subtr(best_with_kicked_l, kicked_v_l, res_l.second, res_r.first);
      combine_subtr(best_with_kicked_r, kicked_v_r, res_r.second, res_l.first);
      if (best_with_kicked_l > best_with_kicked_r) {
        ans.second = std::move(kicked_v_l);
      } else {
        ans.second = std::move(kicked_v_r);
      }
    }
    return std::move(ans);
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
  init_tree(1, 1, n);
  //cout << "tree inited\n";

  for (int i = 0; i < q; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    auto res = query(1, 1, n, l, r);
    printf("%d %d\n", res.second[0].second, depth[res.second[0].first]);
  }
  return 0;
}
