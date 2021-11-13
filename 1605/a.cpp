#include <iostream>
#include <cstdio>

using namespace std;

int mabs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

int solve() {
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  int start = a + c - 2 * b;
  return (start % 3) ? 1 : 0;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    printf("%d\n", solve());
  }
}
