#include <iostream>
#include <cstdio>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);
  if (n % 2) {
    printf("-1\n");
  } else {
    printf("%d 0 0\n", n / 2);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
