#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

vector<int> directions;

void print_direction(int dir) {
  switch (dir) {
    case UP:
      printf("UP\n");
      break;
    case DOWN:
      printf("DOWN\n");
      break;
    case LEFT:
      printf("LEFT\n");
      break;
    case RIGHT:
      printf("RIGHT\n");
      break;
  }
}

int main() {
  int n;
  int p_x, p_y;

  scanf("%d", &n);
  scanf("%d %d", &p_x, &p_y);

  for (int i = 0; i < n; ++i) {
    int c_x, c_y;
    scanf("%d %d", &c_x, &c_y);
    if (c_x == p_x) {
      if (c_y < p_y) {
        directions.push_back(DOWN);
      } else {
        directions.push_back(UP);
      }
    } else {
      if (c_x < p_x) {
        directions.push_back(LEFT);
      } else {
        directions.push_back(RIGHT);
      }
    }
    p_x = c_x;
    p_y = c_y;
  }

  int ans = 0;
  for (int i = 0; i < directions.size() - 1; ++i) {
    //print_direction(directions[i]);
    //print_direction(directions[i + 1]);
    if ((directions[i] == UP && directions[i + 1] == LEFT) ||
        (directions[i] == LEFT && directions[i + 1] == DOWN) ||
        (directions[i] == DOWN && directions[i + 1] == RIGHT) ||
        (directions[i] == RIGHT && directions[i + 1] == UP)) {
      //cout << "INC\n";
      ++ans;
    }
  }
  cout << ans << "\n";

  return 0;
}
