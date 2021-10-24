#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <ctime>

using namespace std;

const int MAXN = 1005;

int n;
vector<int> g[MAXN];
int sz[MAXN];
bool used[MAXN];

// basically finds a centroid
int dfs(int v, int p, int all_sz, pair<int, int>& ctr) {
  sz[v] = 1;
  for (auto to: g[v]) {
    if (!used[to] && to != p && !ctr.first) {
      int cur_sub_sz = dfs(to, v, all_sz, ctr);
      if (ctr.first) {
        sz[v] = all_sz - cur_sub_sz;
        return 0;
      }

      sz[v] += cur_sub_sz;
    }
  }

  int up_sz = all_sz - sz[v];
  if (!ctr.first && up_sz <= all_sz / 2) {
    ctr = {v, p};
  }

  return sz[v];
}

void get_rec_children(int v, int p, set<int>& res) {
  //cout << "get_rec_child " << v << ", " << p << endl;
  res.insert(v);

  for (auto to: g[v]) {
    if (to != p && !used[to]) {
      get_rec_children(to, v, res);
    }
  }
}

int query(set<int>& v) {
  cout << "? " << v.size() << " ";
  for (auto el: v) {
    cout << el << " ";
  }
  cout << "\n";
  int dist;
  cin >> dist;
  return dist;
}

void ans(int a, int b) {
  cout << "! " << a << " " << b << "\n";
  cout.flush();
}

int main() {
  srand(time(nullptr));
  cin >> n;

  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    cin >> from >> to;
    g[from].push_back(to);
    g[to].push_back(from);
  }

  set<int> query_v;
  for (int i = 1; i <= n; ++i) { query_v.insert(i); }
  int target = query(query_v);

  pair<int, int> cur_v{0, 0};
  int cur = 1;
  for (;;) {
    dfs(cur, 0, n, cur_v);

    query_v.clear();
    vector<pair<int, int>> szs;

    // cout << "centroid: " << cur_v.first << endl;

    for (auto to: g[cur_v.first]) {
      if (!used[to]) {
        szs.emplace_back(sz[to], to);
        // cout << "sz:("<< to << "): "  << sz[to] << endl;
      }
    }
    random_shuffle(szs.begin(), szs.end());
    // sort(szs.begin(), szs.end());

    if (szs.size() == 1) {
      ans(cur_v.first, szs.front().second);
      return 0;
    }

    int sum_sz = 0;
    // get_rec_children(szs[0].second, cur_v.first, query_v);

    int i = 0;
    while (i < szs.size() && sum_sz + szs[i].first <= n / 2) {
      sum_sz += szs[i].first;
      get_rec_children(szs[i].second, cur_v.first, query_v);
      ++i;
    }

    query_v.insert(cur_v.first);
    if (query(query_v) != target) {
      for (int j = 0; j < i; ++j) {
        // cout << "cut: " << szs[j].second << endl;
        n -= szs[j].first;
        used[szs[j].second] = true;
      }
    } else {
      for (int j = i; j < szs.size(); ++j) {
        // cout << "cut: " << szs[j].second << endl;
        n -= szs[j].first;
        used[szs[j].second] = true;
      }
    }

    cur = cur_v.first;
    cur_v = {0, 0};
  }
}
