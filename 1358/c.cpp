#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;


void solve() {
  int x1, x2, y1, y2;
  scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
  printf("%lld\n", (x2 - x1) * 1ll * (y2 - y1) + 1);
}


int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
