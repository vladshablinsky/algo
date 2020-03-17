#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int MAXN = 1000;
const int HALF = 500;
const int ROOKS_CNT = 666;
int cell[MAXN][MAXN];
pair<int, int> id_to_cell_map[ROOKS_CNT + 5];
int king_x, king_y;

void init() {
  scanf("%d%d", &king_x, &king_y);
  for (int i = 0; i < ROOKS_CNT; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    cell[x][y] = i + 1;
    id_to_cell_map[i + 1] = {x, y};
  }
}

void finish_game() {
  exit(0);
  cout.flush();
}

void process_rook_move() {
  int k, x, y;
  cin >> k >> x >> y;
  if (k == -1 || k == 0) {
    finish_game();
  }

  int prev_x, prev_y;
  std::tie(prev_x, prev_y) = id_to_cell_map[k];
  id_to_cell_map[k] = {x, y};
  cell[prev_x][prev_y] = 0;
  cell[x][y] = k;
}

void send_cur_pos() {
  cout << king_x << " " << king_y << "\n";
}

void move_to_center() {
  while (king_x != HALF) {
    if (king_x < HALF) {
      king_x++;
    } else {
      king_x--;
    }
    send_cur_pos();
  }
  while (king_y != HALF) {
    if (king_y < HALF) {
      king_y++;
    } else {
      king_y--;
    }
    send_cur_pos();
  }
}

void move_to_corner() {
  int ul = 0, ur = 0, bl = 0, br = 0;
  for (int i = 1; i <= ROOKS_CNT; ++i) {
    int x = id_to_cell_map[i].first;
    int y = id_to_cell_map[i].second;

    if (x < HALF) {
      if (y < HALF) {
        ++ul;
      } else {
        ++ur;
      }
    } else {
      if (y < HALF) {
        ++bl;
      } else {
        ++br;
      }
    }
  }

  int dx, dy;
  if (ul + ur > bl + br) {
    dx = -1;
    if (bl > br) {
      dy = -1;
    } else {
      dy = 1;
    }
  } else {
    dx = 1;
    if (ul > ur) {
      dy = -1;
    } else {
      dy = 1;
    }
  }

  for (int i = 0; i < HALF - 1; ++i) {
    king_x = king_x + dx;
    king_y = king_y + dy;
    if (cell[king_x][king_y]) {
      king_x -= dx;
      send_cur_pos();
      finish_game();
    } else {
      send_cur_pos();
    }
  }
}

int main() {
  init();
  move_to_center();
  move_to_corner();
  return 0;
}
