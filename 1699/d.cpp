#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

constexpr int kMaxN = 5005;
constexpr int kInf = 1000000000;

void solve() {
  int n;
  scanf("%d", &n);

  vector<int> a(n);
  unordered_map<int, vector<int>> indices;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    indices[a[i]].push_back(i);
  }

  // f(i,j) whether i...j can be eliminated
  vector<vector<int>> f(n, vector<int>(n, 0));
  for (int i = 0; i < n; ++i) {
    vector<int> cnts(kMaxN, 0);
    int max_cnt = 1;
    cnts[a[i]]++;
    for (int j = i + 1; j < n; ++j) {
      cnts[a[j]]++;
      max_cnt = max(max_cnt, cnts[a[j]]);

      if (auto len = (j - i + 1); len % 2 == 0 && max_cnt <= len / 2) {
        f[i][j] = 1;
      }
    }
  }

  // debug output
  // for (int i = 0; i < n; ++i) {
  //   for (int j = 0; j < n; ++j) {
  //     printf("%d ", f[i][j]);
  //   }
  //   printf("\n");
  // }

  int ans = 0;

  // g
  // go through all unique elements and calculate dp for them
  // g_el(i) is the maximum cnt of el's we can leave eliminating other
  // elements if we've have considere i first el's and we take i'th
  //
  // NOTE: first and last are dummies and we always take them
  for (auto& [el, ind_v]: indices) {
    vector<int> g_el(indices[el].size() + 2, -kInf);
    g_el[0] = 0;

    for (int i = 1; i <= ind_v.size() + 1; ++i) {

      // iterate the last we took so that we
      // eliminate from next of it till i
      for (int j = 0; j < i; ++j) {

        // This we take
        int i_idx = i > ind_v.size() ? n : ind_v[i - 1];

        // Try as if we had took it
        int j_idx = j ? ind_v[j - 1] : -1;

        int extra = i != (ind_v.size() + 1);
        if (j_idx + 1 > i_idx - 1 || f[j_idx + 1][i_idx - 1]) {
          g_el[i] = max(g_el[i], g_el[j] + extra);
        }
      }
    }
    ans = max(ans, g_el.back());
  }
  printf("%d\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
