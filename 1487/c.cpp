#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 105;
int mx[MAXN][MAXN];

void solve() {
  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int edge = 1;
      if (j - i > n / 2) {
        edge = -1;
      } else if (n % 2 == 0 && j - i == n / 2) {
        edge = 0;
      }

      printf("%d ", edge);
    }
  }
  printf("\n");
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
