#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

const int INF = 1e9;
const int MAXN = 10;
const int PIECES = 3;

const int KNIGHT = 0;
const int BISHOP = 1;
const int ROOK = 2;

int grid[MAXN][MAXN];
bool used[MAXN][MAXN][PIECES];
pair<int, int> d[MAXN][MAXN][PIECES][MAXN][MAXN][PIECES];
pair<int, int> f[MAXN * MAXN][PIECES];
pair<int, int> pos[MAXN * MAXN];

void init_used(int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < PIECES; ++k) {
        used[i][j][k] = false;
      }
    }
  }
}

vector<tuple<int, int, int>> moves_from(tuple<int, int, int> &cell, int n) {
  int i, j, piece;
  std::tie(i, j, piece) = cell;
  vector<tuple<int, int, int>> ans;
  if (piece == KNIGHT) {
    for (int di = -2; di <= 2; ++di) {
      for (int dj = -2; dj <= 2; ++dj) {
        if (abs(di) + abs(dj) == 3 && i + di >= 0 && i + di < n &&
            j + dj >= 0 && j + dj < n) {
          ans.push_back({i + di, j + dj, piece});
        }
      }
    }
  } else if (piece == BISHOP) {
    for (int k = 1; k < n; ++k) {
      if (i + k < n && j + k < n) {
        ans.push_back({i + k, j + k, piece});
      }
      if (i - k >= 0 && j - k >= 0) {
        ans.push_back({i - k, j - k, piece});
      }
      if (i - k >= 0 && j + k < n) {
        ans.push_back({i - k, j + k, piece});
      }
      if (i + k < n && j - k >= 0) {
        ans.push_back({i + k, j - k, piece});
      }
    }
  } else {
    for (int k = 1; k < n; ++k) {
      if (i + k < n) {
        ans.push_back({i + k, j, piece});
      }
      if (i - k >= 0) {
        ans.push_back({i - k, j, piece});
      }
      if (j + k < n) {
        ans.push_back({i, j + k, piece});
      }
      if (j - k >= 0) {
        ans.push_back({i, j - k, piece});
      }
    }
  }
  // add these moves in the end, so less piece changes are processed first!
  ans.push_back({i, j, (piece + 1) % PIECES});
  ans.push_back({i, j, (piece + 2) % PIECES});
  return ans;
}

void bfs(int start_i, int start_j, int start_piece, int n) {
  init_used(n);
  d[start_i][start_j][start_piece][start_i][start_j][start_piece] = {0, 0};
  queue<tuple<int, int, int>> q;
  q.push({start_i, start_j, start_piece});
  used[start_i][start_j][start_piece] = true;
  while (!q.empty()) {
    auto cell = q.front();
    int from_i, from_j, from_piece;
    tie(from_i, from_j, from_piece) = cell;
    q.pop();
    for (auto &cell_to: moves_from(cell, n)) {
      int to_i, to_j, to_piece;
      tie(to_i, to_j, to_piece) = cell_to;

      if (!used[to_i][to_j][to_piece]) {
        used[to_i][to_j][to_piece] = true;
        auto &d_to = d[start_i][start_j][start_piece][to_i][to_j][to_piece];
        d_to = d[start_i][start_j][start_piece][from_i][from_j][from_piece];
        if (from_piece == to_piece) {
          d_to.first++;
        } else {
          d_to.second++;
        }
        q.push(cell_to);
      }
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &grid[i][j]);
      pos[grid[i][j] - 1] = {i, j};
      for (int k = 0; k < PIECES; ++k) {
        bfs(i, j, k, n);
      }
    }
  }

  for (int piece = 0; piece < PIECES; ++piece) {
    f[0][piece] = {0, 0};
  }
  int from_i, from_j;
  tie(from_i, from_j) = pos[0];

  for (int x = 1; x < n * n; ++x) {
    int to_i, to_j;
    tie(to_i, to_j) = pos[x];


    for (int piece = 0; piece < PIECES; ++piece) {
      f[x][piece] = {INF, INF};

      for (int from_piece = 0; from_piece < PIECES; ++from_piece) {
        const auto &cur_d = d[from_i][from_j][from_piece][to_i][to_j][piece];

        if ((f[x - 1][from_piece].first + f[x - 1][from_piece].second +
            cur_d.first  + cur_d.second) < f[x][piece].first + f[x][piece].second) {
          f[x][piece].first = f[x - 1][from_piece].first + cur_d.first;
          f[x][piece].second = f[x - 1][from_piece].second + cur_d.second;
        } else if ((f[x - 1][from_piece].first + f[x - 1][from_piece].second +
            cur_d.first  + cur_d.second) == (f[x][piece].first + f[x][piece].second) &&
            f[x - 1][from_piece].second + cur_d.second < f[x][piece].second) {
          f[x][piece].first = f[x - 1][from_piece].first + cur_d.first;
          f[x][piece].second = f[x - 1][from_piece].second + cur_d.second;
        }
      }

    }
    from_i = to_i;
    from_j = to_j;
  }

  pair<int, int> ans = {INF, INF};
  for (int piece = 0; piece < PIECES; ++piece) {
    if (f[n * n - 1][piece].first + f[n * n - 1][piece].second < ans.first + ans.second) {
      ans = f[n * n - 1][piece];
    } else if (f[n * n - 1][piece].first + f[n * n - 1][piece].second == ans.first + ans.second &&
        f[n * n - 1][piece].second < ans.second) {
      ans = f[n * n - 1][piece];
    }
  }
  cout << ans.first + ans.second << " " << ans.second << "\n";
  return 0;
}
