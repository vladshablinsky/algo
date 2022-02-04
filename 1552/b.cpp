#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);
  vector<vector<int>> v(n);
  for (int i = 0; i < n; ++i) {
    v[i].resize(5);
    for (int j = 0; j < 5; ++j) {
      scanf("%d", &v[i][j]);
    }
  }

  auto check_superioty = [&](int i, int j) -> bool {
    int cnt_i_sup_j = 0;
    for (int k = 0; k < 5; ++k) {
      if (v[i][k] < v[j][k]) {
        ++cnt_i_sup_j;
      }
    }
    // printf("check superioty %d %d %d\n", i, j, cnt_i_sup_j);
    return cnt_i_sup_j >= 3;
  };

  int cur_sup = 0;
  for (int i = 1; i < n; ++i) {
    if (!check_superioty(cur_sup, i)) {
      cur_sup = i;
    }
  }

  bool is_ok = true;
  for (int i = 0; i < n; ++i) {
    if (i != cur_sup && !check_superioty(cur_sup, i)) {
      is_ok = false;
      break;
    }
  }

  if (is_ok) {
    printf("%d\n", cur_sup + 1);
  } else {
    printf("-1\n");
  }
}

int main() {
  int t;
  scanf("%d", &t);

  while (t--) {
    solve();
  }
}
