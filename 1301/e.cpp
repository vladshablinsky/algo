#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 502;
char grid[MAXN][MAXN];

int max_range[MAXN][MAXN][MAXN];
vector<pair<int, int>> centers[MAXN];

bool check(int s_i, int s_j, int f_i, int f_j, int d_i, int d_j, char target) {
  while (true) {
    if (grid[s_i][s_j] != target) {
      return false;
    }

    if (s_i == f_i && s_j == f_j) {
      break;
    }
    s_i += d_i;
    s_j += d_j;
  }

  return true;
}

// ii -- red bottom right row
// jj -- red bottom right col
bool check_border(int ii, int jj, int d) {
  //cout << "checking " << ii << ", " << jj << " d=" << d << endl;
  return check(ii, jj - d + 1, ii - d + 1, jj - d + 1, -1, 0, 'R') &&
    check(ii - d + 1, jj - d + 1, ii - d + 1, jj, 0, 1, 'R') &&
    check(ii - d + 1, jj + 1, ii - d + 1, jj + d, 0, 1, 'G') &&
    check(ii - d + 1, jj + d, ii, jj + d, 1, 0, 'G') &&
    check(ii + d, jj + 1, ii + d, jj + d, 0, 1, 'B') &&
    check(ii + 1, jj + d, ii + d, jj + d, 1, 0, 'B') &&
    check(ii + 1, jj - d + 1, ii + d, jj - d + 1, 1, 0, 'Y') &&
    check(ii + d, jj - d + 1, ii + d, jj, 0, 1, 'Y');
}

int main() {
  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);

  for (int i = 0; i < n; ++i) {
    scanf("%s", grid[i]);
  }

  for (int j = 0; j < m - 1; ++j) {
    for (int i = 0; i < n - 1; ++i) {
      int d = 0;
      while (i - d >= 0 && j - d >= 0 && i + d < n && j + d < m &&
          check_border(i, j, d + 1)) {
        ++d;
      }
      if (d) {
        centers[j].emplace_back(i, d);
      }
    }
  }

  for (int j = 0; j < m - 1; ++j) {
    int first_center_idx = 0;
    auto &centers_j = centers[j];
    for (int from = 0; from < n - 1; ++from) {
      while (first_center_idx < centers_j.size() && centers_j[first_center_idx].first < from) {
        ++first_center_idx;
      }

      if (first_center_idx >= centers[j].size()) {
        break;
      }

      int cur_max = 0;
      int last_open = first_center_idx;
      int forward = 0;
      int backward = 0;
      for (int to = from; to < n; ++to) {
        if (last_open + 1 < centers_j.size() && centers_j[last_open + 1].first == to) {
          last_open++;
        }

        if (centers_j[last_open].first <= to) {
          if (centers_j[last_open].first + centers_j[last_open].second >= to) {
            forward = to - centers_j[last_open].first;
          } else {
            forward = centers[j][last_open].second;
          }

          if (centers_j[last_open].first - centers_j[last_open].second + 1 <= from) {
            backward = centers_j[last_open].first - from + 1;
          } else {
            backward = centers_j[last_open].second;
          }
        } else {
          forward = 0;
          backward = 0;
        }

        max_range[j][from][to] = max(cur_max, min(backward, forward));
        cur_max = max(cur_max, max_range[j][from][to]);
      }
    }
  }
  for (int i = 0; i < q; ++i) {
    int r1, c1, r2, c2;
    scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
    --r1; --c1; --r2; --c2;
    int ans = 0;
    int max_square_on_vert = 0;
    for (int vert = c1; vert < c2; ++vert) {
      max_square_on_vert = min(min(vert - c1 + 1, c2 - vert), max_range[vert][r1][r2]);
      ans = max(ans, max_square_on_vert);
    }
    printf("%d\n", ans * ans * 4);
  }

  return 0;
}
