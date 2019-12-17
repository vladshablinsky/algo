#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int MAXN = 1000;

vector<int> rows[MAXN];
vector<int> cols[MAXN];
pair<vector<int>, int> sq_rows[MAXN];
pair<vector<int>, int> sq_cols[MAXN];

pair<vector<int>, int> squeeze(vector<int> a) {
  map<int, int> mp;

  for (auto &el: a) {
    mp[el] = 0;
  }

  int i = 1;
  for (auto &el: mp) {
    el.second = i++;
  }

  vector<int> ans(a.size());
  for (int i = 0; i < a.size(); ++i) {
    ans[i] = mp[a[i]];
  }
  return {ans, int(mp.size())};
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int el;
      scanf("%d", &el);
      rows[i].push_back(el);
    }
    sq_rows[i] = squeeze(rows[i]);
  }

  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n; ++i) {
      cols[j].push_back(rows[i][j]);
    }
    sq_cols[j] = squeeze(cols[j]);
  }

  for (int i = 0; i < n; ++i) {
    // intersection
    for (int j = 0; j < m; ++j) {
      auto sq_row = sq_rows[i];
      auto sq_col = sq_cols[j];

      int cnt_ls_row = sq_row.first[j] - 1;
      int cnt_gr_row = sq_row.second - sq_row.first[j];
      int cnt_ls_col = sq_col.first[i] - 1;
      int cnt_gr_col = sq_col.second - sq_col.first[i];

      cout << max(cnt_ls_row, cnt_ls_col) + max(cnt_gr_row, cnt_gr_col) + 1 << " ";

    }
    cout << "\n";
  }
  return 0;
}
