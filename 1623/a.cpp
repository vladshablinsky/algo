#include <iostream>
#include <cstdio>

using namespace std;

void solve() {
  int n, m;
  int r_s, c_s;
  int r_target, c_target;
  scanf("%d%d%d%d%d%d", &n, &m, &r_s, &c_s, &r_target, &c_target);

  int dr = 1;
  int dc = 1;
  int cnt = 0;
  for (;;) {
    if (r_s == r_target || c_s == c_target) {
      break;
    }

    if (n != 1 && (r_s + dr > n || r_s + dr < 1)) {
      dr *= -1;
    }

    if (m != 1 && (c_s + dc > m || c_s + dc < 1)) {
      dc *= -1;
    }
    r_s += dr;
    c_s += dc;
    ++cnt;
  }
  printf("%d\n", cnt);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
