#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 61;

void solve () {
  int n;
  scanf("%d", &n);
  int cnt_ones = 0;
  int cnt_zeros = 0;
  int el;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &el);
    cnt_ones += el == 1;
    cnt_zeros += el == 0;
  }

  // empty subsequence -- ok
  printf("%lld\n", cnt_ones * (1 << cnt_zeros));
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
