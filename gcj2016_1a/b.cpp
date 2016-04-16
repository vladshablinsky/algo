#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

const int MAXN_NUM = 2505;

int cnt[MAXN_NUM];
int n;

void init() {
  for (int i = 0; i < MAXN_NUM; ++i) {
    cnt[i] = 0;
  }
}

void solve(int id) {
  init();
  scanf("%d", &n);
  for (int i = 0; i < 2 * n - 1; ++i) {
    for (int j = 0; j < n; ++j) {
      int t;
      scanf("%d", &t);
      cnt[t]++;
    }
  }
  printf("Case #%d: ", id);
  for (int i = 0; i < MAXN_NUM; ++i) {
    if (cnt[i] % 2 != 0) {
      printf("%d ", i);
    }
  }
  printf("\n");
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve(i + 1);
  }

  return 0;
}
