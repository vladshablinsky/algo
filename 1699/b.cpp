#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int sample[4][4] = {
  {0, 1, 1, 0},
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {0, 1, 1, 0},
};

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int ii = i % 4;
      int jj = j % 4;
      cout << sample[ii][jj] << " ";
    }
    cout << "\n";
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
