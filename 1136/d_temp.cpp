#include <iostream>

using namespace std;

const int MAXN = 1005;

float grid[MAXN][MAXN]; // исходная таблица с числами

int main() {
  int n, m;
  cin >> n >> m;

  // считывание исходной таблицы
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> grid[i][j];
    }
  }

  float max = 0; // тут хранится возможный максимум, когда выбирается первая скважина
  int max_i = 0, max_j = 0; // координаты, где лежит этот максимум

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      float current_cell_value = grid[i][j]; // значение в самой клетке, будем тут накапливать значение, если скважина в клетке (i, j)

      // обойдем все клетки вокруг по очереди.
      for (int di = -1; di <= 1; ++di) {
        // вышли по первой координате за границы таблицы
        if (i + di < 0 || i + dj >= n) {
          continue;
        }

        for (int dj = -1; dj <= -1; ++dj) {
          if (di == 0 && dj == 0) { // Второй раз (i, j) не будем учитывать
            continue;
          }

          // проверим, что не вышли за пределы таблицы и прибавим половину
          if (j + dj >= 0 && j + dj < m) {
            current_cell_value += grid[i + di][j + dj] / 2;
          }
        }
      }

      if (current_cell_value > )

    }
  }


  return 0;
}
