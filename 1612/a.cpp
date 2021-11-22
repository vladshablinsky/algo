#include <iostream>
#include <cstdio>

using namespace std;

int mabs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

void solve() {
  int x, y;
  scanf("%d%d", &x, &y);

  if ((x + y) % 2) {
    printf("-1 -1\n");
    return;
  } else {
    for (int i = 0; i <= 50; ++i) {
      for (int j = 0; j <= 50; ++j) {
        if (i + j == (x + y) / 2 &&
            (mabs(i - x) + mabs(j - y) == (x + y) / 2)) {
          printf("%d %d\n", i, j);
          return;
        }
      }
    }
  }
  printf("-1 -1\n");
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
