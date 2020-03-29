#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAXN = 300005;
string perm = "ACGT";

int n, m;
string grid[MAXN];
string ans[MAXN];
int absolute_min = INF;
int shift[MAXN];

void solve() {
  int cur_cost = 0;
  for (int i = 0; i < n; ++i) {
    int cost_no_shift = 0;
    int cost_shift = 0;
    for (int j = 0; j < m; ++j) {
      cost_no_shift += (perm[(i % 2) * 2 + (j % 2)] != grid[i][j]);
      cost_shift += (perm[(i % 2) * 2 + ((j + 1) % 2)] != grid[i][j]);
    }
    cur_cost += min(cost_no_shift, cost_shift);
    shift[i] = (cost_no_shift > cost_shift);
  }

  if (cur_cost < absolute_min) {
    absolute_min = cur_cost;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        ans[i][j] = perm[(i % 2) * 2 + (j + shift[i]) % 2];
      }
  }
}

void solve_transposed() {
  int cur_cost = 0;
  for (int j = 0; j < m; ++j) {
    int cost_no_shift = 0;
    int cost_shift = 0;
    for (int i = 0; i < n; ++i) {
      cost_no_shift += (perm[(j % 2) * 2 + (i % 2)] != grid[i][j]);
      cost_shift += (perm[(j % 2) * 2 + ((i + 1) % 2)] != grid[i][j]);
    }
    cur_cost += min(cost_no_shift, cost_shift);
    shift[j] = (cost_no_shift > cost_shift);
  }

  if (cur_cost < absolute_min) {
    absolute_min = cur_cost;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        ans[i][j] = perm[(j % 2) * 2 + (i + shift[j]) % 2];
      }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    cin >> grid[i];
    ans[i].resize(m);
  }

  do {
    solve();
    solve_transposed();
  } while (next_permutation(perm.begin(), perm.end()));

  for (int i = 0; i < n; ++i) {
    cout << ans[i] << "\n";
  }
  //cout << absolute_min << endl;
  return 0;
}
