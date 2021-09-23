#include <iostream>

using namespace std;

int get_cnt_skip(int n, int k) {
  if (n % 2 == 0) {
    return 0;
  }
  return k / ((n - 1) / 2);
}

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  printf("%d\n", (k - 1 + get_cnt_skip(n, k - 1)) % n + 1);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
