#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 105;
int a[MAXN];

int solve() {
  int n, l, r, k;
  scanf("%d%d%d%d", &n, &l, &r, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  sort(a, a + n);

  int cur_spent = 0;
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    if (cur_spent + a[i] > k) {
      break;
    }

    if (a[i] >= l && a[i] <= r) {
      cur_spent += a[i];
      ++cnt;
    }
  }
  return cnt;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    printf("%d\n", solve());
  }
}
