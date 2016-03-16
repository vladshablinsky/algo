#include <iostream>
#include <cstdio>
#include <set>
#include <vector>

using namespace std;

int ans [105][105];

int main() {
  int n;
  int a, b;
  scanf("%d", &n);
  scanf("%d%d", &a, &b);

  int cnt_odd = (n + 1) / 2;
  int cnt_even = n / 2;

  int odd_space = (a * b + 1) / 2;
  int even_space = (a * b) / 2;

  if (cnt_odd > odd_space || cnt_even > even_space) {
    printf("-1\n");
    return 0;
  }

  bool reverse = false;

  int cur = 1;
  for (int i = 0; i < a; ++i) {
    for (int j = 0; j < b; ++j) {
      if (cur <= n) {
        ans[i][j] = cur++;
      }
    }
  }

  for (int i = 0; i < a; ++i) {
    for (int j = 0; j < b; ++j) {
      if (reverse) {
        printf("%d ", ans[i][b - 1 - j]);
      } else {
        printf("%d ", ans[i][j]);
      }
    }
    printf("\n");
    if (b % 2 == 0) {
      reverse = !reverse;
    }
  }
  return 0;
}
