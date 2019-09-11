#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 300005;
const int MAXK = 19;

int a[MAXN];
int r_with_bit[MAXK];
bool answers[MAXN];
// queries[i][j] is (k, l) where i is L, k is R and l is number of query;
vector<pair<int, int>> queries[MAXN];

vector<int> g[MAXN];
int used[MAXN];

int rank_v[MAXN];
int parent_v[MAXN];

void init_sets(int n) {
  for (int i = 0; i < n; ++i) {
    parent_v[i] = i;
    rank_v[i] = 1;
  }
}

int find_set(int x) {
  if (x == parent_v[x]) {
    return x;
  }
  return parent_v[x] = find_set(parent_v[x]);
}

void unite(int x, int y) {
  // cout << "unite " << x << ", " << y << endl;
  int a = find_set(x);
  int b = find_set(y);
  if (a != b) {
    if (rank_v[a] < rank_v[b]) {
      swap(a, b);
    }

    parent_v[b] = a;
    rank_v[a] += rank_v[b];
  }
}

void dfs(int v) {
  used[v] = true;
  for (auto to: g[v]) {
    if (!used[to]) {
      dfs(to);
    }
    unite(v, to);
  }
}

int main() {
  int n, q;

  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  for (int i = 0; i < q; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    --l; --r;
    queries[l].push_back({r, i});
  }

  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j < MAXK; ++j) {
      if (a[i] & (1 << j)) {
        if (r_with_bit[j] > i) {
          g[i].push_back(r_with_bit[j]);
        }
        r_with_bit[j] = i;
      }
    }
  }

  init_sets(n);
  for (int cur_l = 0; cur_l < n; ++cur_l) {
    // cout << "cur_l is " << cur_l << endl;
    if (!used[cur_l]) {
      dfs(cur_l);
    }

    for (int j = 0; j < queries[cur_l].size(); ++j) {
      int cur_r = queries[cur_l][j].first;
      int query_id = queries[cur_l][j].second;

      int cur_l_set = find_set(cur_l);
      int cur_r_set = find_set(cur_r);

      // cout << "set for " << cur_r << ": " << cur_r_set << endl;
      // cout << "set for " << cur_l << ": " << cur_l_set << endl;

      if (cur_l_set == cur_r_set) {
        answers[query_id] = true;
        // cout << "answer " << query_id << " is true\n";
      }
    }
  }

  for (int i = 0; i < q; ++i) {
    if (answers[i]) {
      cout << "Shi\n";
    } else {
      cout << "Fou\n";
    }
  }
  return 0;
}
