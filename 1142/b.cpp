#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

const int MAX_N = 2e5 + 10;
const int INF = 1e9;
const int NONE = -1;

int n, m, q;
int a[MAX_N];
int p[MAX_N];

vector<vector<int>> g(MAX_N);
vector<int> min_idx(MAX_N, INF);
vector<int> max_idx(MAX_N, -INF);
vector<int> t_min(4 * MAX_N);
vector<int> t_max(4 * MAX_N);
vector<bool> used(MAX_N);

void dfs(int v, vector<int> &sequence, bool reversed=false) {
  if (sequence.size() >= n) {
    int first = *(sequence.end() - n);
    int last = v;
    if (reversed) {
      swap(first, last);
    }
    min_idx[first] = min(min_idx[first], last);
    max_idx[last] = max(max_idx[last], first);
    // cout << "last = " << last << ", min_idx[" << first << "] = " << min_idx[first] << endl;
    // cout << "first = " << first << ", max_idx[" << last << "] = " << max_idx[last] << endl;
    //char c;
    //cin >> c;
  }

  for (auto to: g[v]) {
    if (!used[to]) {
      // cout << "from " << v <<  " to " << to << endl;
      used[to] = true;
      sequence.push_back(to);
      dfs(to, sequence, reversed);
      sequence.pop_back();
    }
  }
}

void calc_with_g(bool reversed) {
  g.clear();
  g.resize(m);
  vector<int> prv(n + 1);
  vector<int> latest(MAX_N, NONE);

  for (int i = 0; i < n; ++i) {
    int prev_idx = (i - 1 + n) % n; // i -> i + 1
    if (reversed) {             // i <- i + 1
      prev_idx = (i + 1) % n;
    }

    prv[p[i]] = p[prev_idx];
  }

  for (int i = 0; i < m; ++i) {
    int idx = i;
    if (reversed) {
      idx = m - i - 1;
    }

    int from;
    if ((from = latest[prv[a[idx]]]) != NONE) {
      g[from].push_back(idx);
      // cout << "add (" << from << ", " << idx << ")\n";
    }
    latest[a[idx]] = idx;
  }

  for (int i = 0; i < m; ++i) {
    used[i] = false;
  }
  for (int i = 0; i < m; ++i) {
    int idx = i;
    if (reversed) {
      idx = m - i - 1;
    }
    if (!used[idx]) {
      used[idx] = true;
      vector<int> seq{idx};
      dfs(idx, seq, reversed);
    }
  }
}

void build_tree(int v, int tl, int tr) {
  if (tl == tr) {
    t_min[v] = min_idx[tl];
    t_max[v] = max_idx[tl];
  } else {
    int tm = (tl + tr) / 2;
    build_tree(v * 2, tl, tm);
    build_tree(v * 2 + 1, tm + 1, tr);
    t_min[v] = min(t_min[v * 2], t_min[v * 2 + 1]);
    t_max[v] = max(t_max[v * 2], t_max[v * 2 + 1]);
  }
}

int query_min(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return INF;
  }
  if (tl == l && tr == r) {
    return t_min[v];
  }

  int tm = (tl + tr) / 2;
  return min(query_min(v * 2, tl, tm, l, min(r, tm)),
      query_min(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}

int query_max(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return -INF;
  }
  if (tl == l && tr == r) {
    return t_max[v];
  }

  int tm = (tl + tr) / 2;
  return max(query_max(v * 2, tl, tm, l, min(r, tm)),
      query_max(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}

int main() {
  cin >> n >> m >> q;
  vector<int> nxt(n + 1);

  for (int i = 0; i < n; ++i) {
    cin >> p[i];
  }

  for (int i = 0; i < m; ++i) {
    cin >> a[i];
  }

  calc_with_g(true);
  calc_with_g(false);
  build_tree(1, 0, m);

  // cout << "=====================\n";
  // for (int i = 0; i < m; ++i) {
  //   cout << "i: " << i << " ";
  //   if (min_idx[i] != INF) {
  //     cout << min_idx[i] << " ";
  //   } else {
  //     cout << "X ";
  //   }
  //   cout << endl;
  // }
  // cout << endl;

  string result;
  for (int i = 0; i < q; ++i) {
    int l, r;
    cin >> l >> r;
    if (query_min(1, 0, m, l - 1, r - n) <= r - 1 ||
        query_max(1, 0, m, l + n, r - 1) >= l - 1) {
      // cout << "1\n";
      result.push_back('1');
    } else {
      // cout << "0\n";
      result.push_back('0');
    }
  }
  cout << result << "\n";
  return 0;
}
