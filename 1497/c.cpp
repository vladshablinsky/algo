#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

void solve_3(int n, int k) {
  if (n % 2) {
    printf("1 %d %d\n", (n - 1) / 2, (n - 1) / 2);
  } else if (((n - 2) / 2) % 2) {
    printf("%d %d %d\n", n / 4, n / 4, n / 2);
  } else {
    printf("2 %d %d\n", (n - 2) / 2, (n - 2) / 2);
  }
}

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  while (k != 3) {
    printf("1 ");
    --k;
    --n;
  }
  solve_3(n, k);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
