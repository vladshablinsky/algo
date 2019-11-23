#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;

const int MAXN = 105;
const string ids = "abcdefghijklmnoprstquvwxyzABCDEFGHIJKLMNOPRSTQUVWXYZ0123456789";

enum class Dir {
  LEFT, DOWN, RIGHT, UP
};

Dir next(Dir cur) {
  auto res = static_cast<Dir>((static_cast<int>(cur) + 1) % 4);
  return res;
}

string grid[MAXN];

void solve() {
  int r, c, k;
  int rice_cnt = 0;
  cin >> r >> c >> k;
  for (int i = 0; i < r; ++i) {
    cin >> grid[i];
    for (int j = 0; j < c; ++j) {
      rice_cnt += grid[i][j] == 'R';
    }
  }

  int cnt_per_chic = rice_cnt / k;
  int cnt_chics_with_extra = rice_cnt % k;

  // cout << "cnt_per_chic = " << cnt_per_chic << ", cnt_chics_with_extra: " << cnt_chics_with_extra << endl;

  int l_bound = 0;
  int r_bound = c - 1;
  int u_bound = 0;
  int d_bound = r - 1;
  Dir cur_state;
  if (c > 1) {
    cur_state = Dir::LEFT;
    u_bound = 1;
  } else {
    cur_state = Dir::DOWN;
    l_bound = 1;
  }


  int cur_cnt = 0;
  int cur_chic_id_idx = 0;
  int i = 0, j = c - 1;

  for (int cur = 0; cur < r * c; ++cur) {
    // cout << "(" << i << ", " << j << ")";
    cur_cnt += grid[i][j] == 'R';
    if (cur_cnt > cnt_per_chic && !cnt_chics_with_extra) {
      cur_cnt = 1;
      ++cur_chic_id_idx;
    } else if (cur_cnt > cnt_per_chic + 1) {
      cur_cnt = 1;
      --cnt_chics_with_extra;
      ++cur_chic_id_idx;
    }
    grid[i][j] = ids[cur_chic_id_idx];

    switch(cur_state) {
      case Dir::LEFT:
        --j;
        if (j == l_bound) {
          ++l_bound;
          cur_state = next(cur_state);
        }
        break;
      case Dir::DOWN:
        ++i;
        if (i == d_bound) {
          --d_bound;
          cur_state = next(cur_state);
        }
        break;
      case Dir::RIGHT:
        ++j;
        if (j == r_bound) {
          --r_bound;
          cur_state = next(cur_state);
        }
        break;
      case Dir::UP:
        --i;
        if (i == u_bound) {
          ++u_bound;
          cur_state = next(cur_state);
        }
        break;
    }
    //  // cout << "-> (" << i << ", " << j << ")\n";
  }

  for (int i = 0; i < r; ++i) {
    cout << grid[i] << "\n";
  }
}


int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
