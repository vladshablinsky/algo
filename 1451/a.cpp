#include <iostream>
#include <cstdio>

using namespace std;

int solve_x(int x) {
  if (x == 1) {
    return 0;
  } else if (x == 2) {
    return 1;
  } else if (x & 1) {
    return 1 + solve_x(x - 1);
  } else {
    return 2;
  }
}

int solve() {
  int n;
  scanf("%d", &n);
  return solve_x(n);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    printf("%d\n", solve());
  }
}
