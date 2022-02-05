#include <iostream>
#include <cstdio>

using namespace std;

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  if (n == 4 && k == 3) {
    printf("-1\n");
  } else if (k == n - 1) {
    printf("%d %d\n", n - 1, n - 2);
    printf("1 %d\n", n - 3);
    printf("0 2\n");
    for (int i = 1; i <= n / 2 - 3; ++i) {
      printf("%d %d\n", 2 + i, n - 3 - i);
    }
  } else {
    printf("%d %d\n", k, n - 1);
    if (k != 0) {
      printf("0 %d\n", n - k - 1);
    }
    for (int i = 1; i < n / 2; ++i) {
      if (i != k && n - 1 - i != k) {
        printf("%d %d\n", i, n - 1 - i);
      }
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
