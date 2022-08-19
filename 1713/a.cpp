#include <iostream>
#include <cstdio>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);

  int min_l = 0;
  int max_r = 0;
  int min_d = 0;
  int max_u = 0;
  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    min_l = min(x, min_l);
    max_r = max(x, max_r);
    min_d = min(min_d, y);
    max_u = max(max_u, y);
  }
  printf("%d\n",
      2 * ((abs(min_l) + abs(max_r) + abs(min_d) + abs(max_u))));
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
