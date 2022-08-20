#include <iostream>
#include <cstdio>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);
  int i = 1;
  if (n & 1) {
    printf("1 ");
    ++i;
  }
  for (; i + 1 <= n; i += 2) {
    printf("%d %d ", i + 1, i);
  }
  printf("\n");
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
