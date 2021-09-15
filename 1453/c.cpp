#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 2005;
const int MAXD = 10;
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int NONE = -1;
int bounds[MAXD][4];
string grid[MAXN];

void init_bounds() {
  for (int i = 0; i < MAXD; ++i) {
    for (int j = 0; j < 4; ++j) {
      bounds[i][j] = NONE;
    }
  }
}

void ensure_any(int dig, int i, int j) {
  if (bounds[dig][UP] == NONE) {
    bounds[dig][UP] = i;
    bounds[dig][DOWN] = i;
    bounds[dig][LEFT] = j;
    bounds[dig][RIGHT] = j;
  }
}

void solve() {
  init_bounds();
  int n;
  cin >> n;

  // NOTE: Reading lines from bottom to top
  for (int i = 0; i < n; ++i) {
    cin >> grid[i];
    for (int j = 0; j < n; ++j) {
      int d = grid[i][j] - '0';
      ensure_any(d, i, j);

      bounds[d][LEFT] = min(bounds[d][LEFT], j);
      bounds[d][RIGHT] = max(bounds[d][RIGHT], j);

      bounds[d][UP] = i;
      // DOWN is ensured on initialize
    }
  }

  vector<int> ans(MAXD, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int d = grid[i][j] -'0';
      int cur_space_h_base = max(n - j - 1, j) * max(bounds[d][UP] - i, i - bounds[d][DOWN]);
      int cur_space_v_base = max(n - i - 1, i) * max(bounds[d][RIGHT] - j, j - bounds[d][LEFT]);
      ans[d] = max(ans[d], max(cur_space_h_base, cur_space_v_base));
    }
  }

  for (auto ans_d: ans) {
    printf("%d ", ans_d);
  }
  printf("\n");
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
