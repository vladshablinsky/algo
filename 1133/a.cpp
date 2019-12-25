#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

const int DELTAS_CNT = 4;
// right, left, down, up
const pair<int, int> DELTAS[DELTAS_CNT] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

struct Cell {
    int x;
    int y;
    Cell(int x, int y): x(x), y(y) {};
};

int minimumDays(int rows, int columns, vector<vector<int> > grid)
{
    // The algorithm is pretty similar to bfs. Zero day we push all updated
    // servers to queue and then we pop servers one ofter another from
    // the beginning of the queut and push their adjacent not-yet-updated
    // servers back to the queue. We'll continue the process untill the queue is
    // empty which will mean that all the servers got updated.
    // While pushing into the queue we'll remember the day the push to queue
    // happens: the logic behind that is to know minimum day for the server
    // it gets updated. Then if minumum update day for some server in queue is x
    // then by the time it is extracted all not-yet-updated adjacent servers'
    // minimum update day is x + 1. The answer is then max minimum update
    // days among all the servers.


    // queue of pairs (a, b) where are is a day when server b begins sending updates
    queue<pair<int, Cell> > q;

    // Add zero-day servers that will send the updates imediately.
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (grid[i][j]) {
                q.push({0, Cell(i, j)});
            }
        }
    }

    int ans = 0; // max days till update of some server
    while (!q.empty()) {
        int cur_day = q.front().first;
        Cell cur_cell = q.front().second;
        q.pop();
        ans = max(cur_day, ans);
        cout << "front: " << cur_cell.x << " " << cur_cell.y << endl;
        cout << "cur_day " << cur_cell.x << " " << cur_cell.y << " Is " << cur_day << endl;

        for (int i = 0; i < DELTAS_CNT; ++i) {
            int to_x = cur_cell.x + DELTAS[i].first;
            int to_y = cur_cell.y + DELTAS[i].second;
            cout << "to_x: " << to_x << endl;
            cout << "to_y: " << to_y << endl;
            if (to_x >= 0 && to_x < rows && to_y >= 0 && to_y < columns && !grid[to_x][to_y]) {
              cout << "push " << cur_day + 1 << "to_x, to_y" << endl;
                q.push({cur_day + 1, Cell(to_x, to_y)});
                grid[to_x][to_y] = 1;
            }
        }
    }

    return ans;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0 ; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int t;
      cin >> t;
      g[i].push_back(t);
    }
  }
  cout << minimumDays(n, m, g) << endl;
  return 0;
}
