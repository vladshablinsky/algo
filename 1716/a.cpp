#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);
  int ans = n / 3;
  int rem = n % 3;

  if (rem == 1) {
    if (ans) {
      ++ans;
    } else {
      ans = 2;
    }
  } else if (rem == 2) {
    ++ans;
  }

  printf("%d\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
