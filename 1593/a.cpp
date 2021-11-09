#include <iostream>
#include <cstdio>

using namespace std;

int dominate(int a, int b, int c) {
  if (a > max(b, c)) {
    return 0;
  }

  return max(b, c) + 1 - a;
}

void solve() {
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  printf("%d %d %d\n", dominate(a, b, c), dominate(b, a, c), dominate(c, a, b));
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
