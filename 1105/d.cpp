#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

const int MAXN = 1002;
const int MAXP = 10;

int di[4] = {1, -1, 0, 0};
int dj[4] = {0, 0, -1, 1};

bool used[MAXN][MAXN];
string grid[MAXN];
int s[MAXP];
int cnt_occupied_by[MAXP];
vector<pair<int, int>> player_castles_to_expand[MAXP];

int main() {
  int n, m, p;
  cin >> n >> m >> p;
  for (int i = 0; i < p; ++i) {
    cin >> s[i];
  }

  for (int i = 0; i < n; ++i) {
    cin >> grid[i];
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] >= '1' && grid[i][j] <= '9') {
        int p_id = grid[i][j] - '1';
        player_castles_to_expand[p_id].push_back({i, j});
        used[i][j] = true;
        cnt_occupied_by[p_id]++;
      }
      if (grid[i][j] == '#') {
        used[i][j] = true;
      }
    }
  }

  bool all_empty = false;
  while (!all_empty) {
    all_empty = true;
    for (int i = 0; i < p; ++i) {
      // perform little local bfs
      queue<pair<pair<int, int>, int>> q;
      for (auto cell: player_castles_to_expand[i]) {
        q.push({cell, 0});
      }
      player_castles_to_expand[i].clear();

      while (!q.empty()) {
        int ii = q.front().first.first;
        int jj = q.front().first.second;
        int d = q.front().second;
        q.pop();
        if (d == s[i]) {
          continue;
        }

        for (int dt_i = 0; dt_i < 4; ++dt_i) {
          int to_ii = ii + di[dt_i];
          int to_jj = jj + dj[dt_i];
          if (to_ii >= 0 && to_jj >= 0 && to_ii < n && to_jj < m &&
              !used[to_ii][to_jj]) {
            used[to_ii][to_jj] = true;
            cnt_occupied_by[i]++;
            q.push({make_pair(to_ii, to_jj), d + 1});
            player_castles_to_expand[i].push_back({to_ii, to_jj});
          }
        }
      }

      if (!player_castles_to_expand[i].empty()) {
        all_empty = false;
      }
    }
  }
  for (int i = 0; i < p; ++i) {
    cout << cnt_occupied_by[i] << " ";
  }
  cout << "\n";
  return 0;
}
