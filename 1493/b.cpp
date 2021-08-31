#include <iostream>
#include <cstdio>

using namespace std;

pair<int, bool> reflect(int x) {
  static int mapping[10] = {0, 1, 5, -1, -1, 2, -1, -1, 8, -1};
  return {mapping[x], mapping[x] != -1};
}

bool is_valid(int hh, int mm, int h, int m) {
  return hh < h && mm < m;
}

bool is_valid_reflected(int hh, int mm, int h, int m) {
  auto [h1, valid_h1] = reflect(hh / 10);
  auto [h2, valid_h2] = reflect(hh % 10);
  auto [m1, valid_m1] = reflect(mm / 10);
  auto [m2, valid_m2] = reflect(mm % 10);

  if (!(valid_h1 & valid_h2 & valid_m1 & valid_m2)) {
    return false;
  }

  return is_valid(m2 * 10 + m1, h2 * 10 + h1, h, m);
}

void solve() {
  int h, m;
  int hh, mm;
  scanf("%d%d", &h, &m);
  scanf("%d:%d", &hh, &mm);

  while (!is_valid_reflected(hh, mm, h, m)) {
    ++mm;
    if (mm == m) {
      ++hh;
      mm = 0;
    }

    if (hh == h) {
      hh = 0;
    }
  }
  printf("%02d:%02d\n", hh, mm);
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
