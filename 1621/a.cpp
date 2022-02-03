#include <iostream>
#include <cstdio>

using namespace std;

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  if ((n + 1) / 2 < k) {
    printf("-1\n");
  } else {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == j && i % 2 == 0 && k) {
          --k;
          printf("R");
        } else {
          printf(".");
        }
      }
      printf("\n");
    }
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
