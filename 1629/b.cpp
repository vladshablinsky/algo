#include <iostream>
#include <cstdio>

using namespace std;

int cnt_odd(int r) {
  return (r + 1) / 2;
}

bool solve() {
  int l, r, k;
  scanf("%d%d%d", &l, &r, &k);

  if (l == r) {
    return l != 1;
  }

  return cnt_odd(r) - cnt_odd(l - 1) <= k;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    if (solve()) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
}
